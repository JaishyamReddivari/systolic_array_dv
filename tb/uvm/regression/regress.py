#!/usr/bin/env python3
"""Seeded regression runner for systolic_array_dv.

Builds the binaries via make, runs each test across a seed sweep (direct
binary invocation so the seed varies and the raw log is captured), merges
code coverage across seeds, and consolidates pass/fail + coverage into a
JSON report. Exits non-zero on any failure so it can gate CI.

Run from the sim directory (the one with the makefile and obj_dir/).
"""
import argparse
import json
import os
import shutil
import subprocess
import sys

from log_parser import parse_log, passed
from cov_parser import parse_coverage

BIN_TOP  = "./obj_dir/Vtb_top"
BIN_CTRL = "./obj_dir/Vtb_ctrl"
BIN_COV  = "./obj_dir_cov/Vtb_top_cov"
COV_DAT  = "coverage.dat"

# test name -> binary that runs it
TESTS = {
    "single_tile_test": BIN_CTRL,
    "top_tile_test":    BIN_TOP,
    "multi_tile_test":  BIN_TOP,
}

# optional: demote the spurious UVM/COMP/NAME warnings (no source change)
QUIET = "+uvm_set_action=*,UVM/COMP/NAME,UVM_WARNING,UVM_NO_ACTION"


def sh(cmd, timeout=300):
    try:
        p = subprocess.run(cmd, stdout=subprocess.PIPE,
                           stderr=subprocess.STDOUT, text=True, timeout=timeout)
        return p.stdout, p.returncode
    except subprocess.TimeoutExpired as e:
        return (e.stdout or "") + "\n[TIMEOUT]", 124


def build(coverage):
    targets = ["build_top", "build_ctrl"] + (["build_cov"] if coverage else [])
    print(f"building: make {' '.join(targets)}")
    out, rc = sh(["make", *targets])
    if rc != 0:
        print(out)
        sys.exit("build failed")


def run_sim(binary, test, seed, quiet_names):
    cmd = [binary, f"+UVM_TESTNAME={test}", f"+verilator+seed+{seed}"]
    if quiet_names:
        cmd.append(QUIET)
    out, _ = sh(cmd)
    return out


def run_functional(tests, seeds, quiet_names):
    rows = []
    for test in tests:
        for seed in seeds:
            res = parse_log(run_sim(TESTS[test], test, seed, quiet_names))
            ok = passed(res)
            rows.append({"test": test, "seed": seed, "pass": ok, **res})
            tag = "PASS" if ok else "FAIL"
            if ok and (res["sb_checked"] or 0) == 0:
                tag = "PASS*"                      # vacuous: passed but checked nothing
            print(f"  [{tag}] {test:<16} seed={seed:<3} "
                  f"checked={res['sb_checked']} mism={res['sb_mismatches']} "
                  f"err={res['errors']} warn={res['warnings']}")
    return rows


def run_coverage(seeds, quiet_names):
    dats = []
    for seed in seeds:
        run_sim(BIN_COV, "multi_tile_test", seed, quiet_names)
        if not os.path.exists(COV_DAT):
            print(f"  warn: no {COV_DAT} produced for seed {seed}")
            continue
        dat = f"cov_seed_{seed}.dat"
        shutil.move(COV_DAT, dat)
        dats.append(dat)
    if not dats:
        return {}
    merged = "coverage_merged.dat"
    sh(["verilator_coverage", "--write", merged, *dats])
    summary, _ = sh(["verilator_coverage", merged])
    for d in dats:
        os.remove(d)
    return parse_coverage(summary)


def main():
    ap = argparse.ArgumentParser(description="systolic_array_dv regression")
    ap.add_argument("--seeds", type=int, default=5, help="run seeds 1..N")
    ap.add_argument("--tests", nargs="+", default=list(TESTS), choices=list(TESTS))
    ap.add_argument("--no-coverage", action="store_true")
    ap.add_argument("--quiet-names", action="store_true",
                    help="demote the spurious UVM/COMP/NAME warnings at runtime")
    ap.add_argument("--report", default="regression_report.json")
    args = ap.parse_args()
    seeds = list(range(1, args.seeds + 1))
    want_cov = not args.no_coverage

    build(coverage=want_cov)

    print(f"\nfunctional regression: {len(args.tests)} tests x {len(seeds)} seeds")
    rows = run_functional(args.tests, seeds, args.quiet_names)

    cov = {}
    if want_cov:
        print(f"\ncode coverage: merging {len(seeds)} seeds")
        cov = run_coverage(seeds, args.quiet_names)
        for m, d in cov.items():
            print(f"  {m:<10}: {d['pct']:>5.1f}% ({d['hit']}/{d['total']})")

    n_fail = sum(1 for r in rows if not r["pass"])
    func = next((r["func_cov"] for r in rows
                 if r["test"] == "multi_tile_test" and r["func_cov"]), {})

    print("\n==== regression summary ====")
    print(f"  runs        : {len(rows)}")
    print(f"  failures    : {n_fail}")
    vacuous = sum(1 for r in rows if r["pass"] and (r["sb_checked"] or 0) == 0)
    print(f"  vacuous     : {vacuous} (passed but checked 0 tiles)")
    if func:
        all_100 = all(v == 100.0 for v in func.values())
        print(f"  func cov    : {'all coverpoints 100%' if all_100 else func}")
    if cov:
        line = cov.get("line", {}).get("pct", "?")
        branch = cov.get("branch", {}).get("pct", "?")
        print(f"  code cov    : line {line}%  branch {branch}%")
    warns = {r["warnings"] for r in rows if r["warnings"] is not None}
    if warns and not args.quiet_names:
        print(f"  warnings    : {sorted(warns)} (spurious UVM/COMP/NAME; see docs)")

    with open(args.report, "w") as f:
        json.dump({"runs": rows, "code_cov": cov,
                   "func_cov": func, "failures": n_fail}, f, indent=2)
    print(f"  report      : {args.report}")

    sys.exit(1 if n_fail else 0)


if __name__ == "__main__":
    main()
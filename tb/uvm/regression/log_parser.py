"""Parse a UVM/Verilator simulation log into a structured result dict."""
import re

_RE_REPORT = re.compile(r'^UVM_(ERROR|FATAL|WARNING)\s*:\s*(\d+)', re.M)
_RE_SB     = re.compile(r'\[SB\]\s+checked=(\d+)\s+mismatches=(\d+)')
_RE_TILES  = re.compile(r'\[TEST\]\s+ran\s+(\d+)\s+tiles')
_RE_FINISH = re.compile(r'\$finish')
_RE_COVPT  = re.compile(r'(\w+)=([\d.]+)%')

_SEV_KEY = {"ERROR": "errors", "FATAL": "fatals", "WARNING": "warnings"}


def parse_log(text):
    r = {"errors": None, "fatals": None, "warnings": None,
         "sb_checked": None, "sb_mismatches": None,
         "tiles": None, "finished": False, "func_cov": {}}

    for m in _RE_REPORT.finditer(text):
        r[_SEV_KEY[m.group(1)]] = int(m.group(2))

    m = _RE_SB.search(text)
    if m:
        r["sb_checked"] = int(m.group(1))
        r["sb_mismatches"] = int(m.group(2))

    m = _RE_TILES.search(text)
    if m:
        r["tiles"] = int(m.group(1))

    r["finished"] = bool(_RE_FINISH.search(text))

    # functional coverage headline (the one [COV] line carrying CP1_A=...)
    for line in text.splitlines():
        if "[COV]" in line and "CP1_A=" in line:
            r["func_cov"] = {k: float(v) for k, v in _RE_COVPT.findall(line)}
            break

    return r


def passed(r):
    """A run passes if the report summary parsed, no errors/fatals, the sim
    reached $finish, and (when present) the scoreboard saw 0 mismatches.
    UVM_WARNING is intentionally not a failure criterion."""
    if r["errors"] is None or r["fatals"] is None:
        return False
    if r["errors"] != 0 or r["fatals"] != 0:
        return False
    if not r["finished"]:
        return False
    if r["sb_mismatches"] is not None and r["sb_mismatches"] != 0:
        return False
    return True

def verified(r):
    """Passed AND actually exercised the scoreboard (non-vacuous)."""
    return passed(r) and (r["sb_checked"] or 0) > 0
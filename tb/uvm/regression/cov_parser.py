"""Parse `verilator_coverage` summary text into a metrics dict."""
import re

_RE_METRIC = re.compile(
    r'^\s*(line|toggle|branch|expr|fsm_state|fsm_arc)\s*:\s*'
    r'([\d.]+)%\s*\(\s*(\d+)\s*/\s*(\d+)\)', re.M)


def parse_coverage(text):
    out = {}
    for m in _RE_METRIC.finditer(text):
        out[m.group(1)] = {
            "pct": float(m.group(2)),
            "hit": int(m.group(3)),
            "total": int(m.group(4)),
        }
    return out
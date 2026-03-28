//Auther name: Ankita Ghising
//Date : 2024-06-17
import os
from collections import Counter
from pathlib import Path

import matplotlib

matplotlib.use("Agg")
import matplotlib.pyplot as plt
import pandas as pd
from matplotlib.ticker import FuncFormatter

// Read CSV file path
BASE = Path(__file__).resolve().parent.parent
_CLEAN_A = BASE / "data" / "clean" / "departments_clean.csv"
_CLEAN_B = BASE / "output" / "departments_clean.csv"
CHART_DIR = BASE / "output" / "charts"

// Handle chunk size and chart parameters via environment variables
CHUNK = int(os.environ.get("CHARTS_CHUNK_ROWS", "50000"))
DPI, FIG_W, FIG_H_MAX = 100, 10, 16
TOP_CITY, TOP_TYPE, TOP_SPEC = 15, 12, 20
LABEL_MAX = 42
COLS = ["City", "DepartmentType", "DepartmentSpecialty"]


def clean_path():
    if _CLEAN_A.is_file() and _CLEAN_B.is_file():
        return _CLEAN_A if _CLEAN_A.stat().st_mtime >= _CLEAN_B.stat().st_mtime else _CLEAN_B
    if _CLEAN_A.is_file():
        return _CLEAN_A
    if _CLEAN_B.is_file():
        return _CLEAN_B
    raise FileNotFoundError("Run 01_clean_departments.py first (no departments_clean.csv found).")


def bucket(v):
    if pd.isna(v) or str(v).strip() == "":
        return "Unspecified / Unknown"
    return str(v).strip()


def short(s, m=LABEL_MAX):
    s = str(s).strip()
    return s if len(s) <= m else s[: m - 3] + "..."


def top_n(s, n, other):
    s = s.sort_values(ascending=False)
    if len(s) <= n:
        return s
    h = s.iloc[:n].copy()
    h[other] = int(s.iloc[n:].sum())
    return h


def scan_counts(path: Path, chunk_size: int):
    head = pd.read_csv(path, nrows=0)
    bad = [c for c in COLS if c not in head.columns]
    if bad:
        raise ValueError(f"Missing columns {bad}")

    ctr = {c: Counter() for c in COLS}
    total = 0
    for part in pd.read_csv(path, usecols=COLS, chunksize=chunk_size):
        total += len(part)
        for c in COLS:
            ctr[c].update(part[c].map(bucket).value_counts().to_dict())

    def to_series(c):
        return pd.Series(dict(c), dtype="int64").sort_values(ascending=False)

    return to_series(ctr["City"]), to_series(ctr["DepartmentType"]), to_series(ctr["DepartmentSpecialty"]), total


def fmt_k(x, _):
    try:
        return f"{int(round(x)):,}"
    except (ValueError, TypeError, OverflowError):
        return ""


def barh(series, title, xlabel, path, color="steelblue"):
    s = series.sort_values(ascending=True).copy()
    s.index = [short(i) for i in s.index.astype(str)]
    h = min(max(4.0, 0.32 * len(s) + 1.2), FIG_H_MAX)
    fig, ax = plt.subplots(figsize=(FIG_W, h))
    s.plot(kind="barh", ax=ax, color=color)
    ax.set_title(title)
    ax.set_xlabel(xlabel)
    ax.xaxis.set_major_formatter(FuncFormatter(fmt_k))
    fig.subplots_adjust(left=0.28, right=0.97, top=0.92, bottom=0.12)
    fig.savefig(path, dpi=DPI)
    plt.close(fig)


def main():
    p = clean_path()
    CHART_DIR.mkdir(parents=True, exist_ok=True)

    city, typ, spec, n = scan_counts(p, CHUNK)
    print(f"Rows scanned: {n:,}")

    barh(top_n(city, TOP_CITY, "All other cities"), f"Cities (top {TOP_CITY} + other)", "Count", CHART_DIR / "departments_by_city.png")
    barh(top_n(typ, TOP_TYPE, "All other types"), f"Types (top {TOP_TYPE} + other)", "Count", CHART_DIR / "department_type_distribution.png")
    barh(top_n(spec, TOP_SPEC, "All other specialties"), f"Specialties (top {TOP_SPEC} + other)", "Count", CHART_DIR / "department_specialty_breakdown.png", "seagreen")

    print(f"Charts: {CHART_DIR}")


if __name__ == "__main__":
    main()

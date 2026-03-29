#Auther name: Ankita Ghising
#Date : 2024-06-17
import os

#Handle thread settings for performance
os.environ.setdefault("OMP_NUM_THREADS", "1")
os.environ.setdefault("OPENBLAS_NUM_THREADS", "1")
os.environ.setdefault("MKL_NUM_THREADS", "1")
os.environ.setdefault("NUMEXPR_MAX_THREADS", "1")

import pandas as pd
from pathlib import Path

CHUNK_ROWS = int(os.environ.get("DEPARTMENTS_CHUNK_ROWS", "25000"))

#Read CSV file path
BASE = Path(__file__).resolve().parent.parent
RAW_DIR = BASE / "data" / "raw"
_RAW = (RAW_DIR / "departments.csv", RAW_DIR / "departments_sample.csv")
OUT_MAIN = BASE / "data" / "clean" / "departments_clean.csv"
OUT_FALLBACK = BASE / "output" / "departments_clean.csv"

STAR = {"*Unspecified", "*Unknown", "*Not Applicable", "*Deleted", "Deleted", ""}
STAR_COLS = ["County", "DepartmentSpecialty", "DepartmentType"]

CITY_JUNK = {"", "nan", "none", "na", "*unknown", "*unspecified", "*not applicable", "*deleted", "deleted"}
CITY_JUNK_TITLE = {"*Unknown", "*Unspecified", "*Not Applicable", "*Deleted"}


def clean_city(v):
    s = " ".join(str(v).strip().split())
    if s.lower() in CITY_JUNK or s in CITY_JUNK_TITLE:
        return pd.NA
    return s.title()


def transform_chunk(chunk: pd.DataFrame) -> pd.DataFrame:
    chunk = chunk.copy()
    chunk["DepartmentKey"] = pd.to_numeric(chunk["DepartmentKey"], errors="coerce")
    chunk = chunk[chunk["DepartmentKey"].notna() & (chunk["DepartmentKey"] > 0)]
    chunk["City"] = chunk["City"].map(clean_city)
    for col in STAR_COLS:
        if col in chunk.columns:
            chunk[col] = chunk[col].astype(str).str.strip().replace({s: "" for s in STAR}).replace("", pd.NA)
    return chunk


def _start_out(first: pd.DataFrame) -> Path:
    OUT_MAIN.parent.mkdir(parents=True, exist_ok=True)
    try:
        first.to_csv(OUT_MAIN, mode="w", header=True, index=False, encoding="utf-8-sig")
        return OUT_MAIN
    except PermissionError:
        OUT_FALLBACK.parent.mkdir(parents=True, exist_ok=True)
        try:
            first.to_csv(OUT_FALLBACK, mode="w", header=True, index=False, encoding="utf-8-sig")
        except PermissionError as e:
            raise PermissionError(
                f"Cannot write CSV (close Excel / read-only / OneDrive). Tried:\n  {OUT_MAIN}\n  {OUT_FALLBACK}"
            ) from e
        print(f"Saved to {OUT_FALLBACK} (data/clean locked)")
        return OUT_FALLBACK


def _raw_path() -> Path:
    for p in _RAW:
        if p.is_file():
            return p
    raise FileNotFoundError(f"Put CSV in {RAW_DIR} as departments.csv or departments_sample.csv")


def main():
    raw = _raw_path()
    dtype = {"PostalCode": str, "CensusTract": str}
    reader = pd.read_csv(raw, dtype=dtype, keep_default_na=False, chunksize=CHUNK_ROWS)

    rows_in = rows_out = 0
    out = None

    for chunk in reader:
        rows_in += len(chunk)
        cleaned = transform_chunk(chunk)
        rows_out += len(cleaned)
        if len(cleaned) == 0:
            continue
        if out is None:
            out = _start_out(cleaned)
        else:
            cleaned.to_csv(out, mode="a", header=False, index=False, encoding="utf-8")

    if out is None:
        empty = pd.read_csv(raw, nrows=0, dtype=dtype, keep_default_na=False)
        out = _start_out(empty)

    print(f"Saved: {out}\nRows in: {rows_in:,}  out: {rows_out:,}")


if __name__ == "__main__":
    main()

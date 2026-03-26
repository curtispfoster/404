"""Create ALS charts from sample CSV data using matplotlib."""

from __future__ import annotations

import csv
from collections import defaultdict
from pathlib import Path

import matplotlib

matplotlib.use("Agg")
import matplotlib.pyplot as plt


def load_rows(csv_path: Path) -> list[dict[str, str]]:
    with csv_path.open("r", encoding="utf-8", newline="") as file:
        return list(csv.DictReader(file))


def build_patient_series(rows: list[dict[str, str]]) -> dict[str, dict[str, list[float]]]:
    series: dict[str, dict[str, list[float]]] = defaultdict(
        lambda: {"month": [], "alsfrs_r": [], "fvc_percent": [], "grip_strength_kg": []}
    )
    for row in rows:
        pid = row["patient_id"]
        series[pid]["month"].append(float(row["month"]))
        series[pid]["alsfrs_r"].append(float(row["alsfrs_r"]))
        series[pid]["fvc_percent"].append(float(row["fvc_percent"]))
        series[pid]["grip_strength_kg"].append(float(row["grip_strength_kg"]))
    return dict(series)


def create_line_chart(patient_series: dict[str, dict[str, list[float]]], output_dir: Path) -> None:
    plt.figure(figsize=(8, 5))
    for pid, values in patient_series.items():
        plt.plot(values["month"], values["alsfrs_r"], marker="o", label=pid)
    plt.title("ALSFRS-R Trend by Patient")
    plt.xlabel("Month")
    plt.ylabel("ALSFRS-R Score")
    plt.grid(alpha=0.3)
    plt.legend()
    plt.tight_layout()
    plt.savefig(output_dir / "alsfrs_trend.png", dpi=150)
    plt.close()


def create_bar_chart(rows: list[dict[str, str]], output_dir: Path) -> None:
    latest = [row for row in rows if row["month"] == "9"]
    ids = [row["patient_id"] for row in latest]
    grip = [float(row["grip_strength_kg"]) for row in latest]

    plt.figure(figsize=(8, 5))
    plt.bar(ids, grip, color="#4E79A7")
    plt.title("Grip Strength at Month 9")
    plt.xlabel("Patient")
    plt.ylabel("Grip Strength (kg)")
    plt.tight_layout()
    plt.savefig(output_dir / "grip_strength_month9.png", dpi=150)
    plt.close()


def create_scatter_chart(rows: list[dict[str, str]], output_dir: Path) -> None:
    fvc = [float(row["fvc_percent"]) for row in rows]
    alsfrs = [float(row["alsfrs_r"]) for row in rows]

    plt.figure(figsize=(8, 5))
    plt.scatter(fvc, alsfrs, color="#F28E2B")
    plt.title("FVC vs ALSFRS-R")
    plt.xlabel("FVC (%)")
    plt.ylabel("ALSFRS-R Score")
    plt.grid(alpha=0.25)
    plt.tight_layout()
    plt.savefig(output_dir / "fvc_vs_alsfrs.png", dpi=150)
    plt.close()


def main() -> None:
    base_dir = Path(__file__).resolve().parent
    csv_path = base_dir / "als_data.csv"
    output_dir = base_dir / "plots"
    output_dir.mkdir(exist_ok=True)

    rows = load_rows(csv_path)
    patient_series = build_patient_series(rows)

    create_line_chart(patient_series, output_dir)
    create_bar_chart(rows, output_dir)
    create_scatter_chart(rows, output_dir)

    print("ALS charts created:")
    print(f"- {output_dir / 'alsfrs_trend.png'}")
    print(f"- {output_dir / 'grip_strength_month9.png'}")
    print(f"- {output_dir / 'fvc_vs_alsfrs.png'}")


if __name__ == "__main__":
    main()

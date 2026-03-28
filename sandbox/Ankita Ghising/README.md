# Department data — clean and charts

Clean a department CSV and build summary bar charts. All files for this mini-project live in this folder.

## What you need

- **Python 3.10+** (3.12 is fine)
- Terminal: **Command Prompt**, **PowerShell**, or **Terminal** (Mac/Linux)

## 1. Install dependencies

Open a terminal, go to this folder (`Ankita Ghising`), then run:

```bash
python3 -m pip install -r requirements.txt
```

On Windows, if `python3` is not found, use:

```bash
py -m pip install -r requirements.txt
```

or:

```bash
python -m pip install -r requirements.txt
```

## 2. Add your data

Put your raw file here:

- `data/raw/departments.csv`

If that file is missing, the script will use `data/raw/departments_sample.csv` instead.

## 3. Run the scripts (in order)

Still inside the `Ankita Ghising` folder:

```bash
python3 scripts/01_clean_departments.py
python3 scripts/02_make_charts.py
```

Windows (same folder):

```bash
py scripts/01_clean_departments.py
py scripts/02_make_charts.py
```

**Step 1** writes a cleaned CSV to `data/clean/departments_clean.csv`. If that path is locked (for example the file is open in Excel), it saves to `output/departments_clean.csv` instead.

**Step 2** reads the newest cleaned file and saves PNG charts under `output/charts/`.

## Folder layout

| Path | Purpose |
|------|---------|
| `data/raw/` | Your input CSV |
| `data/clean/` | Cleaned CSV (when not locked) |
| `output/` | Fallback CSV + charts |
| `scripts/` | `01_clean_departments.py`, `02_make_charts.py` |

## Optional: low-memory computers

If cleaning or charting runs out of memory, use smaller chunks (fewer rows in memory at once).

**Cleaning:**

```bash
# Windows CMD
set DEPARTMENTS_CHUNK_ROWS=10000
py scripts/01_clean_departments.py
```

```powershell
# Windows PowerShell
$env:DEPARTMENTS_CHUNK_ROWS="10000"
py scripts/01_clean_departments.py
```

**Charts:**

```bash
set CHARTS_CHUNK_ROWS=10000
py scripts/02_make_charts.py
```

## Requirements file

Dependencies are listed in `requirements.txt`:

- `pandas`
- `matplotlib`

Reinstall after editing that file with the same `pip install -r requirements.txt` command as above.

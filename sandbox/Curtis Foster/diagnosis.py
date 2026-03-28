import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt

# ====================== CONFIGURATION ======================
FILE_PATH = "diagnosis.csv"
TOP_N = 20
BAD_VALUES = ['Unspecified', 'Unknown', '*Unknown', 'NA', '*Unspecified', 
              'unspecified', 'unknown', 'na', '', 'N/A', 'nan']

# Columns we expect
REQUIRED_COLS = ['GroupCode', 'GroupName']

# ====================== 1. LOAD DATA ======================
def load_data(file_path: str) -> pd.DataFrame:
    """Load CSV file with proper error handling."""
    try:
        df = pd.read_csv(file_path)
        print("✅ File loaded successfully!")
        print(f"Shape: {df.shape[0]:,} rows × {df.shape[1]} columns")
        print(f"Columns: {list(df.columns)}\n")
        return df
    except FileNotFoundError:
        print(f"❌ Error: '{file_path}' not found in the current directory.")
        print("Please make sure the file is in the same folder as this script.")
        raise
    except Exception as e:
        print(f"❌ Error loading file: {e}")
        raise


# ====================== 2. CLEAN DATA ======================
def clean_data(df: pd.DataFrame) -> pd.DataFrame:
    """Clean the diagnosis data."""
    df = df.copy()
    
    # Convert DiagnosisKey to numeric
    if 'DiagnosisKey' in df.columns:
        df['DiagnosisKey'] = pd.to_numeric(df['DiagnosisKey'], errors='coerce')
    
    # Filter out bad/invalid values in DiagnosisKey
    if 'DiagnosisKey' in df.columns:
        mask = ~df['DiagnosisKey'].astype(str).str.strip().str.lower().isin(
            [str(v).strip().lower() for v in BAD_VALUES]
        )
        df_filtered = df[mask].copy()
        print(f"After filtering bad values: {len(df_filtered):,} rows remaining "
              f"({len(df) - len(df_filtered):,} rows removed)\n")
    else:
        df_filtered = df
        print("⚠️  'DiagnosisKey' column not found. Skipping filtering step.\n")
    
    return df_filtered


# ====================== 3. CREATE GROUP SUMMARY ======================
def create_group_summary(df: pd.DataFrame) -> pd.DataFrame:
    """Create summary by GroupCode and GroupName."""
    missing_cols = [col for col in REQUIRED_COLS if col not in df.columns]
    
    if missing_cols:
        print(f"⚠️ Warning: Missing required columns: {missing_cols}")
        print(f"Available columns: {list(df.columns)}")
        return pd.DataFrame()  # Return empty DataFrame
    
    group_summary = (
        df.groupby(['GroupCode', 'GroupName'], dropna=False)
        .agg(
            Total_Count=('DiagnosisKey', 'count'),
            Unique_Keys=('DiagnosisKey', 'nunique')
        )
        .sort_values(by='Total_Count', ascending=False)
        .reset_index()
    )
    
    # Create a readable label for charts
    group_summary['Group_Label'] = (
        group_summary['GroupCode'].astype(str) + 
        " - " + 
        group_summary['GroupName'].astype(str)
    )
    
    return group_summary


# ====================== 4. VISUALIZATION ======================
def plot_top_diagnosis_groups(summary_df: pd.DataFrame, top_n: int = 20):
    """Create a nice horizontal bar chart for top diagnosis groups."""
    if summary_df.empty:
        print("❌ No data available for plotting.")
        return
    
    top_data = summary_df.head(top_n).copy()
    
    plt.figure(figsize=(15, 11))
    
    sns.barplot(
        data=top_data,
        x='Total_Count',
        y='Group_Label',
        hue='Group_Label',
        palette='viridis',
        legend=False,
        edgecolor='black',
        linewidth=0.6
    )
    
    plt.title('Top 20 Diagnosis Groups by Total Count', 
              fontsize=18, pad=25, fontweight='bold')
    plt.xlabel('Total Number of Records', fontsize=14)
    plt.ylabel('')
    
    # Add value labels on bars
    max_count = top_data['Total_Count'].max()
    for i, v in enumerate(top_data['Total_Count']):
        plt.text(v + max_count * 0.012, i, f'{int(v):,}', 
                 va='center', fontsize=11, fontweight='bold')
    
    plt.grid(axis='x', alpha=0.3, linestyle='--')
    plt.tight_layout()
    plt.show()


# ====================== MAIN EXECUTION ======================
if __name__ == "__main__":
    # 1. Load data
    df = load_data(FILE_PATH)
    
    # 2. Clean data
    df_clean = clean_data(df)
    
    # 3. Create summary
    group_summary = create_group_summary(df_clean)
    
    if not group_summary.empty:
        # 4. Plot chart
        print("📊 Generating visualization...")
        plot_top_diagnosis_groups(group_summary, top_n=TOP_N)
        
        # 5. Display top results
        print("\n=== Top 20 Diagnosis Groups ===")
        display_cols = ['GroupCode', 'GroupName', 'Total_Count', 'Unique_Keys']
        print(group_summary.head(20)[display_cols].to_string(index=False))
        
        # 6. Save summary
        output_file = 'diagnosis_groups_summary.csv'
        group_summary.to_csv(output_file, index=False)
        print(f"\n✅ Summary saved as '{output_file}'")
        print(f"Total groups summarized: {len(group_summary):,}")
    else:
        print("❌ Could not create group summary.")

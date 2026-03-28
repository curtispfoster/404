import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt

# ====================== CONFIGURATION ======================
FILE_PATH = "patients.csv"

# Columns you want to analyze
COLUMNS_TO_ANALYZE = [
    'FirstRace', 
    'OmbRace', 
    'OmbEthnicity', 
    'SexAssignedAtBirth',
    'MaritalStatus', 
    'SmokingStatus', 
    'VitalStatus', 
    'MyChartStatus'
]

# ====================== 1. LOAD DATA ======================
def load_data(file_path: str) -> pd.DataFrame:
    """Load the CSV file and print basic info."""
    try:
        df = pd.read_csv(file_path)
        print("✅ File loaded successfully!")
        print(f"Shape: {df.shape[0]:,} rows × {df.shape[1]} columns\n")
        return df
    except FileNotFoundError:
        print(f"❌ Error: File '{file_path}' not found.")
        raise
    except Exception as e:
        print(f"❌ Error loading file: {e}")
        raise


# ====================== 2. ANALYZE CATEGORICAL COLUMNS ======================
def analyze_categorical_columns(df: pd.DataFrame, columns: list):
    """Print value counts for specified columns."""
    print("🔍 Value Counts for key columns:\n")
    
    for col in columns:
        if col in df.columns:
            print(f"--- {col} ---")
            value_counts = df[col].value_counts(dropna=False)
            print(value_counts.head(15))
            print("-" * 60)
        else:
            print(f"⚠️  Column '{col}' not found in the dataset.")


# ====================== 3. BAR CHART FUNCTION ======================
def plot_top_categories(df: pd.DataFrame, column: str, top_n: int = 10, 
                       title: str = None, palette: str = 'viridis'):
    """Create a nice horizontal bar chart for a categorical column."""
    
    if column not in df.columns:
        print(f"❌ Column '{column}' not found.")
        return
    
    # Get top categories
    top_data = df[column].value_counts().head(top_n)
    
    if top_data.empty:
        print(f"No data available for column '{column}'")
        return
    
    # Create plot
    plt.figure(figsize=(12, 8))
    
    ax = sns.barplot(
        x=top_data.values,
        y=top_data.index,
        hue=top_data.index,
        palette=palette,
        legend=False
    )
    
    # Title
    if title is None:
        title = f'Patient Distribution by {column}'
    
    plt.title(title, fontsize=16, pad=20)
    plt.xlabel('Number of Patients')
    plt.ylabel(column)
    plt.grid(axis='x', alpha=0.3)
    
    # Add value labels on bars
    for i, v in enumerate(top_data.values):
        ax.text(v + (v * 0.02), i, f'{v:,}', 
                va='center', fontweight='bold', fontsize=11)
    
    plt.tight_layout()
    plt.show()


# ====================== MAIN EXECUTION ======================
if __name__ == "__main__":
    # Load the data
    df_patients = load_data(FILE_PATH)
    
    # Analyze columns
    analyze_categorical_columns(df_patients, COLUMNS_TO_ANALYZE)
    
    # Example charts - you can easily add more
    print("\n📊 Generating charts...")
    
    plot_top_categories(
        df=df_patients,
        column='OmbRace',
        top_n=10,
        title='Patient Distribution by OMB Race',
        palette='viridis'
    )
    
    # Uncomment to create more charts:
    # plot_top_categories(df_patients, 'OmbEthnicity', title='Patient Distribution by OMB Ethnicity')
    # plot_top_categories(df_patients, 'SexAssignedAtBirth', top_n=5)
    # plot_top_categories(df_patients, 'MaritalStatus')

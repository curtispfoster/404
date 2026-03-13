# Development & Feature Roadmap

## 🔧 Work-in-Progress
This branch is dedicated to **Data Ingestion and Cleaning Logic**. 

## ⚖️ Performance Standards (CIS 2207)
To handle the large-scale DataFest datasets, we are prioritizing:
* **Time Complexity:** Avoiding $O(n^2)$ loops; utilizing HashMaps and optimized sorting where possible.
* **Memory Management:** Efficiently streaming large CSV files rather than loading entire sets into memory when unnecessary.

## 🧪 Testing Protocol
**Ankita:** Please verify the following for all scripts merged from this branch:
1. Handling of Null/Missing values.
2. Data type consistency (e.g., ensuring date columns are formatted correctly).
3. Logic check: Do the output sums/averages align with the raw data samples?

## 📝 Ongoing Tasks
- [ ] Initialize Python/Java environments.
- [ ] Create basic data-loading boilerplate.
- [ ] Establish "Clean Data" schema.

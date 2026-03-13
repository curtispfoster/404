# 🛠️ Feature Branch: Development & Roadmap

This branch is the **active workspace** for **Data Ingestion and Cleaning Logic**.  
All experimental scripts and initial data processing should be developed here before being reviewed for merge into the `main` branch.

## 🌳 Branching & Workflow

- **Main Branch**  
  Reserved for final, stable, and verified competition code.

- **Feature Branch (this one)**  
  Used for active development and peer review.

- **Folder Protocol**  
  Work **must** stay within your assigned subfolder in `/scripts/` to prevent merge conflicts.

## ⚖️ Performance Standards (CIS 2207)

To handle the large-scale DataFest datasets, we are prioritizing **algorithmic efficiency**:

- **Time Complexity**  
  Avoid $O(n^2)$ loops; utilize HashMaps and optimized sorting ($O(n \log n)$) where possible.

- **Memory Management**  
  Efficiently **stream** large CSV files rather than loading entire sets into memory when unnecessary.

## 🧪 Testing Protocol

**Ankita**: Please verify the following for **all scripts** merged from this branch:

1. Handling of **Null/Missing values**
2. **Data type consistency** (e.g., ensuring date columns are formatted correctly)
3. **Logic check**: Do the output sums/averages align with the raw data samples?

## 📝 Ongoing Tasks

- [ ] Initialize Python/Java environments
- [ ] Create basic data-loading boilerplate
- [ ] Establish "Clean Data" schema

## 🗓️ Reference: Official Timeline Template

For the official submission requirements  
(3-slide limit, 5-minute video maximum)  
and the recommended weekend milestones, please refer to:

**Sample Timeline**  
→ Located in the **Main Branch README**

---

Happy coding — let's keep things clean, efficient, and merge-ready! 🚀

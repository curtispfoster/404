#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <filesystem>
#include <sstream>
#include <cctype>
#include <iomanip>

namespace fs = std::filesystem;

const std::vector<std::string> unwanted = {
    "*deleted", "*not applicable", "*unspecified", "*unknown", "na"
};

std::string to_lower_trim(const std::string& str) {
    std::string result;
    result.reserve(str.size());
    for (char c : str) {
        if (!std::isspace(static_cast<unsigned char>(c)) && c != '"') {
            result += static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
        }
    }
    return result;
}

bool contains_unwanted(const std::string& line) {
    if (line.empty()) return false;
    std::stringstream ss(line);
    std::string field;
    while (std::getline(ss, field, ',')) {
        std::string cleaned = to_lower_trim(field);
        if (!cleaned.empty() &&
            std::binary_search(unwanted.begin(), unwanted.end(), cleaned)) {
            return true;
        }
    }
    return false;
}

void process_file(const fs::path& input_path) {
    std::string filename = input_path.filename().string();
    std::string base_name = input_path.stem().string();
    std::string output_path = (input_path.parent_path() / (base_name + "_cleaned.csv")).string();

    std::cout << "Processing: " << filename << "\n";
    std::cout << "Line: ";

    std::ifstream in(input_path, std::ios::in | std::ios::binary);
    std::ofstream out(output_path, std::ios::out | std::ios::binary);

    if (!in.is_open() || !out.is_open()) {
        std::cout << "\rError opening files.\n";
        return;
    }

    std::string line;
    line.reserve(8192);
    size_t row_num = 0;
    size_t kept = 0;
    size_t removed = 0;

    // Live updater settings
    const size_t update_every = 50000;   // Update display every 50,000 lines
    size_t next_update = update_every;

    while (std::getline(in, line)) {
        ++row_num;

        if (row_num == 1) {
            out << line << ",original_row_index\n";
            ++kept;
            continue;
        }

        if (!contains_unwanted(line)) {
            out << line << "," << row_num << "\n";
            ++kept;
        }
        else {
            ++removed;
        }

        // Live line updater
        if (row_num >= next_update) {
            std::cout << "\rLine: " << std::setw(10) << row_num
                << " | Kept: " << kept
                << " | Removed: " << removed
                << std::flush;
            next_update += update_every;
        }
    }

    // Final update
    std::cout << "\rLine: " << std::setw(10) << row_num
        << " | Kept: " << kept
        << " | Removed: " << removed
        << "   [Done]\n";

    in.close();
    out.close();

    std::cout << "  Saved as: " << base_name << "_cleaned.csv\n\n";
}

int main() {
    std::cout << "=== Fast CSV Cleaner with Live Line Updater ===\n";
    std::cout << "Optimized for Intel Core Ultra 7\n\n";

    std::string folder = "Data";
    if (!fs::exists(folder) || !fs::is_directory(folder)) {
        std::cout << "Error: 'Data' folder not found!\n";
        return 1;
    }

    std::vector<fs::path> csv_files;
    for (const auto& entry : fs::directory_iterator(folder)) {
        if (!entry.is_regular_file()) continue;
        std::string ext = entry.path().extension().string();
        std::string stem = entry.path().stem().string();
        if ((ext == ".csv" || ext == ".CSV") &&
            stem.size() >= 8 && stem.substr(stem.size() - 8) != "_cleaned") {
            csv_files.push_back(entry.path());
        }
    }

    if (csv_files.empty()) {
        std::cout << "No CSV files found in Data folder.\n";
        return 0;
    }

    std::sort(csv_files.begin(), csv_files.end());

    std::cout << "Found " << csv_files.size() << " file(s) to process.\n\n";

    for (size_t i = 0; i < csv_files.size(); ++i) {
        std::cout << "File " << (i + 1) << "/" << csv_files.size() << "\n";
        process_file(csv_files[i]);
    }

    std::cout << "\n=== All files cleaned successfully! ===\n";
    std::cout << "Cleaned files are saved with _cleaned suffix in the Data folder.\n";

    return 0;
}

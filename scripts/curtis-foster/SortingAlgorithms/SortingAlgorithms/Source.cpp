/**
 * @file main.cpp
 * @brief Sorting Algorithm Benchmark Program
 *
 * This program measures and compares the execution time of various sorting algorithms
 * (Selection, Bubble, Insertion, Merge, Quick, and Radix Sort) across multiple
 * dataset sizes. It utilizes the <ctime> library for benchmarking and automatically
 * skips O(n^2) algorithms for large datasets to prevent excessive runtimes.
 *
 * @author curtis foster
 * @date Feb 8 - 15, 26
 */

#include "SortingAlgorithms.h"
#include <iostream>
#include <ctime>
#include <string>
#include <iomanip> 

 /**
  * @brief Runs a benchmark for a specific sorting algorithm on a specific array size.
  *
  * This function handles the setup, execution, and timing of a sort. It performs the following steps:
  * 1. Checks if the sort should be skipped (e.g., O(n^2) sorts on large arrays).
  * 2. Resets the target array by copying from the master array to ensure a fair test.
  * 3. Starts the clock.
  * 4. Executes the specified sorting algorithm.
  * 5. Stops the clock and calculates the duration in seconds.
  * 6. Prints the formatted results to the console.
  *
  * @param master[]  The "Master" array containing the original random numbers (read-only).
  * @param target[]  The "Worker" array that will be modified/sorted during the test.
  * @param size      The number of elements in the array.
  * @param sortName  The string name of the algorithm to run (e.g., "Quick", "Merge").
  */
void runTime(const int master[], int target[], int size, std::string sortName);

/**
 * @brief Entry point of the program.
 *
 * Iterates through a predefined list of array sizes (10k, 50k, 100k, 1M).
 * For each size, it:
 * - Allocates memory on the heap for master and target arrays.
 * - Fills the master array with random integers.
 * - Calls runTime() for each of the 6 sorting algorithms.
 * - Frees the allocated memory to prevent leaks.
 *
 * @return Returns 0 upon successful execution.
 */
int main() {
    const int NUM_OF_NUMS = 4;
    const int SIZES[NUM_OF_NUMS] = { 10'000, 50'000, 100'000, 1'000'000 };

    // Set output precision once at the start
    std::cout << std::fixed << std::setprecision(4);

    for (int i = 0; i < NUM_OF_NUMS; ++i) {
        int currentSize = SIZES[i];

        std::cout << "\n--- STARTING TESTS FOR SIZE: " << currentSize << " ---" << std::endl;

        // Allocate memory on the heap
        int* masterArr = new int[currentSize];
        int* array = new int[currentSize];

        // Seed the randomizer with current time
        srand(static_cast<unsigned int>(time(0)));

        for (int j = 0; j < currentSize; j++) {
            masterArr[j] = rand();
        }

        runTime(masterArr, array, currentSize, "Selection");
        runTime(masterArr, array, currentSize, "Bubble");
        runTime(masterArr, array, currentSize, "Insertion");
        runTime(masterArr, array, currentSize, "Merge");
        runTime(masterArr, array, currentSize, "Quick");
        runTime(masterArr, array, currentSize, "Radix");

        // Clean up memory
        delete[] masterArr;
        delete[] array;
    }

    return 0;
}

void runTime(const int master[], int target[], int size, std::string sortName) {
    // Safety check: Skip O(n^2) algorithms for 1 million items
    if (size >= 1000000 && (sortName == "Selection" || sortName == "Bubble" || sortName == "Insertion")) {
        std::cout << std::left << std::setw(12) << sortName
            << "| " << "SKIPPED (O(n^2)) would take several minutes" << std::endl;
        return;
    }

    // Reseting data: Deep copy from master to target
    for (int i = 0; i < size; i++) {
        target[i] = master[i];
    }

    clock_t start = clock();

    if (sortName == "Selection") {
        selectionSort(target, size);
    }
    else if (sortName == "Bubble") {
        bubbleSort(target, size);
    }
    else if (sortName == "Insertion") {
        insertionSort(target, size);
    }
    else if (sortName == "Merge") {
        mergeSort(target, 0, size - 1);
    }
    else if (sortName == "Quick") {
        quickSort(target, 0, size - 1);
    }
    else {
        radixSort(target, size, 10);
    }

    clock_t end = clock();

    double duration = (double)(end - start) / CLOCKS_PER_SEC;

    std::cout << std::left << std::setw(12) << sortName
        << "| " << std::fixed << std::setprecision(6) << duration << "s" << std::endl;
}
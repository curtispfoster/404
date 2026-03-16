#pragma once

/**
 * @author curtis foster
 * @date Feb 8 - 15, 26
 * @brief Sorts an array using the selection sort algorithm.
 *
 * Repeatedly finds the largest element in the unsorted portion
 * and places it at the end of the array.
 *
 * @param arr The array of integers to sort.
 * @param n The number of elements in the array.
 */
void selectionSort(int arr[], int n);

/**
 * @brief Finds the index of the largest element in an array.
 *
 * Searches through the first `size` elements and returns
 * the index of the maximum value.
 *
 * @param arr The array to search.
 * @param size Number of elements to examine.
 * @return Index of the largest value.
 */
int findIndexofLargest(const int arr[], int size);

/**
 * @brief Sorts an array using the bubble sort algorithm.
 *
 * Repeatedly compares adjacent elements and swaps them
 * if they are in the wrong order.
 *
 * @param theArray The array to sort.
 * @param size Number of elements in the array.
 */
void bubbleSort(int theArray[], int size);

/**
 * @brief Sorts an array using the insertion sort algorithm.
 *
 * Builds a sorted portion of the array one element at a time
 * by inserting each new element into its proper position.
 *
 * @param theArray The array to sort.
 * @param size Number of elements in the array.
 */
void insertionSort(int theArray[], int size);


// ==========================
// Faster Sorting Algorithms
// ==========================

/**
 * @brief Sorts an array using the merge sort algorithm.
 *
 * Recursively divides the array into halves, sorts each half,
 * then merges the sorted halves.
 *
 * @param theArray The array to sort.
 * @param start Starting index of the range to sort (inclusive).
 * @param end Ending index of the range to sort (inclusive).
 */
void mergeSort(int theArray[], int start, int end);

/**
 * @brief Merges two sorted subarrays into one sorted range.
 *
 * Assumes:
 * - start → mid is sorted
 * - mid+1 → end is sorted
 *
 * @param theArray The array containing the subarrays.
 * @param start Start index of first subarray.
 * @param mid End index of first subarray.
 * @param end End index of second subarray.
 */
void merge(int theArray[], int start, int mid, int end);

/**
 * @brief Sorts an array using the quick sort algorithm.
 *
 * Recursively partitions the array around a pivot
 * and sorts the resulting subarrays.
 *
 * @param theArray The array to sort.
 * @param start Starting index of the range to sort.
 * @param end Ending index of the range to sort.
 */
void quickSort(int theArray[], int start, int end);

/**
 * @brief Chooses a pivot using the median-of-three method.
 *
 * Rearranges values at start, mid, and end so the median
 * becomes the pivot candidate.
 *
 * @param theArray The array being sorted.
 * @param start First index.
 * @param mid Middle index.
 * @param end Last index.
 */
void medianOfThreePivot(int theArray[], int start, int mid, int end);

/**
 * @brief Partitions an array segment around a pivot.
 *
 * Elements less than the pivot move to the left,
 * elements greater move to the right.
 *
 * @param theArray The array to partition.
 * @param start Start index of the partition range.
 * @param end End index of the partition range.
 * @return Final index of the pivot.
 */
int partition(int theArray[], int start, int end);

/**
 * @brief Sorts integers using radix sort.
 *
 * Performs digit-by-digit sorting from least significant
 * to most significant digit.
 *
 * @param theArray The array to sort.
 * @param size Number of elements in the array.
 * @param digit Number of digits to process.
 */
void radixSort(int theArray[], int size, int digit);

/**
 * @brief Extracts a specific digit from an integer.
 *
 * Used by radix sort to determine bucket placement.
 *
 * @param value The number to extract the digit from.
 * @param j The digit position (1 = least significant).
 * @return The digit at position j.
 */
int getDigit(int value, int j);





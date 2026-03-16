#include "SortingAlgorithms.h"
#include <utility>


/// @file SortingAlgorithms.cpp
/// @brief Implementations of sorting algorithms declared in SortingAlgorithms.h

/// @brief For small quicksort partitions, switch to insertion sort.
static const int MIN_SIZE = 4;

/**
 * @author curtis foster
 * @date Feb 8 - 15, 26
 * @brief Sorts a subrange of an array using insertion sort.
 *
 * This helper is used by quicksort for small partitions so we only sort
 * the requested range [start, end] instead of the whole array.
 *
 * @param theArray The array to sort.
 * @param start Start index (inclusive).
 * @param end End index (inclusive).
 */
static void insertionSortRange(int theArray[], int start, int end) {
	for (int unsorted = start + 1; unsorted <= end; ++unsorted) {
		int nextItem = theArray[unsorted];
		int location = unsorted;

		while ((location > start) && (theArray[location - 1] > nextItem)) {
			theArray[location] = theArray[location - 1];
			--location;
		}

		theArray[location] = nextItem;
	}
}

/** @copydoc selectionSort */
void selectionSort(int arr[], int size) {
	for (int last = size - 1; last >= 1; --last) {
		int largest = findIndexofLargest(arr, last + 1);
		std::swap(arr[largest], arr[last]);
	}
}

/** @copydoc findIndexofLargest */
int findIndexofLargest(const int arr[], int size) {
	int currentIndex = 0;
	for (int index = 1; index < size; ++index) {
		if (arr[index] > arr[currentIndex]) {
			currentIndex = index;
		}
	}
	return currentIndex;
}

/** @copydoc bubbleSort */
void bubbleSort(int theArray[], int size) {
	bool sorted = false;
	int pass = 1;

	while (!sorted && pass < size) {
		sorted = true;

		for (int i = 0; i < size - pass; ++i) {
			int nextIndex = i + 1;
			if (theArray[i] > theArray[nextIndex]) {
				std::swap(theArray[i], theArray[nextIndex]);
				sorted = false;
			}
		}
		++pass;
	}
}

/** @copydoc insertionSort */
void insertionSort(int theArray[], int size) {
	for (int unsorted = 1; unsorted < size; ++unsorted) {
		int nextItem = theArray[unsorted];
		int location = unsorted;

		while ((location > 0) && (theArray[location - 1] > nextItem)) {
			theArray[location] = theArray[location - 1];
			--location;
		}

		theArray[location] = nextItem;
	}
}

/** @copydoc mergeSort */
void mergeSort(int theArray[], int start, int end) {
	if (start < end) {
		int mid = start + (end - start) / 2;
		mergeSort(theArray, start, mid);
		mergeSort(theArray, mid + 1, end);
		merge(theArray, start, mid, end);
	}
}

/** @copydoc merge */
void merge(int theArray[], int start, int mid, int end) {
	int rangeSize = (end - start) + 1;
	int* tempArray = new int[rangeSize];

	int leftStart = start;
	int leftEnd = mid;
	int rightStart = mid + 1;
	int rightEnd = end;

	int index = 0;

	while ((leftStart <= leftEnd) && (rightStart <= rightEnd)) {
		if (theArray[leftStart] <= theArray[rightStart]) {
			tempArray[index] = theArray[leftStart];
			++leftStart;
		}
		else {
			tempArray[index] = theArray[rightStart];
			++rightStart;
		}
		++index;
	}

	while (leftStart <= leftEnd) {
		tempArray[index] = theArray[leftStart];
		++leftStart;
		++index;
	}
	while (rightStart <= rightEnd) {
		tempArray[index] = theArray[rightStart];
		++rightStart;
		++index;
	}

	for (int i = 0; i < rangeSize; ++i) {
		theArray[start + i] = tempArray[i];
	}

	delete[] tempArray;
}

/** @copydoc quickSort */
void quickSort(int theArray[], int start, int end) {
	int size = end - start + 1;

	// ✅ Fix: insertion sort only the subrange [start, end]
	if (size > 0 && size < MIN_SIZE) {
		insertionSortRange(theArray, start, end);
		return;
	}

	if (start < end) {
		int pivotIndex = partition(theArray, start, end);
		quickSort(theArray, start, pivotIndex - 1);
		quickSort(theArray, pivotIndex + 1, end);
	}
}

/** @copydoc medianOfThreePivot */
void medianOfThreePivot(int theArray[], int start, int mid, int end) {
	if (theArray[start] > theArray[mid]) {
		std::swap(theArray[start], theArray[mid]);
	}
	if (theArray[mid] > theArray[end]) {
		std::swap(theArray[mid], theArray[end]);
	}
	// Second swap might have broken the first ordering; restore it.
	if (theArray[start] > theArray[mid]) {
		std::swap(theArray[start], theArray[mid]);
	}
}

/** @copydoc partition */
int partition(int theArray[], int start, int end) {
	int mid = start + (end - start) / 2;
	medianOfThreePivot(theArray, start, mid, end);

	// Put pivot at end-1 (classic median-of-three quicksort setup)
	std::swap(theArray[mid], theArray[end - 1]);
	int pivotIndex = end - 1;
	int pivot = theArray[pivotIndex];

	int leftIndex = start + 1;
	int rightIndex = end - 2;

	// ✅ Fix: add bounds checks to avoid running past the subrange
	while (true) {
		while (leftIndex <= rightIndex && theArray[leftIndex] < pivot) {
			++leftIndex;
		}
		while (leftIndex <= rightIndex && theArray[rightIndex] > pivot) {
			--rightIndex;
		}

		if (leftIndex < rightIndex) {
			std::swap(theArray[leftIndex], theArray[rightIndex]);
			++leftIndex;
			--rightIndex;
		}
		else {
			break;
		}
	}

	// Place pivot into its final position
	std::swap(theArray[pivotIndex], theArray[leftIndex]);
	return leftIndex;
}

/** @copydoc getDigit */
int getDigit(int value, int j) {
	int power = 1;
	for (int i = 1; i < j; ++i) {
		power *= 10;
	}
	return (value / power) % 10;
}

/** @copydoc radixSort */
void radixSort(int theArray[], int size, int digit) {
	// One temp array instead of 10 buckets
	int* output = new int[size];
	int count[10];

	for (int j = 1; j <= digit; ++j) { // LSD: ones -> tens -> ...
		// 1) zero counts
		for (int k = 0; k < 10; ++k) count[k] = 0;

		// 2) count digit frequencies
		for (int i = 0; i < size; ++i) {
			int d = getDigit(theArray[i], j);
			++count[d];
		}

		// 3) prefix sums => positions
		for (int d = 1; d < 10; ++d) {
			count[d] += count[d - 1];
		}

		// 4) stable placement (go right-to-left)
		for (int i = size - 1; i >= 0; --i) {
			int d = getDigit(theArray[i], j);
			output[--count[d]] = theArray[i];
		}

		// 5) copy back
		for (int i = 0; i < size; ++i) {
			theArray[i] = output[i];
		}
	}

	delete[] output;
}

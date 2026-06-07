#include <iostream>
#include <vector>

/* Topic 1: Divide and Conquer Method (Merge Sort)
   Strategy: Divide the unsorted list into n sublists, recursively sort them, 
   and then conquer by merging the sorted sublists.
*/
class DivideAndConquerEngine {
private:
    // Merges two sorted subarrays into a single sorted array
    void merge(std::vector<int>& arr, int left, int mid, int right) {
        int n1 = mid - left + 1;
        int n2 = right - mid;

        std::vector<int> leftArr(n1);
        std::vector<int> rightArr(n2);

        for (int i = 0; i < n1; i++) leftArr[i] = arr[left + i];
        for (int j = 0; j < n2; j++) rightArr[j] = arr[mid + 1 + j];

        int i = 0, j = 0, k = left;
        while (i < n1 && j < n2) {
            if (leftArr[i] <= rightArr[j]) {
                arr[k] = leftArr[i];
                i++;
            } else {
                arr[k] = rightArr[j];
                j++;
            }
            k++;
        }

        // Copy remaining elements if any
        while (i < n1) arr[k++] = leftArr[i++];
        while (j < n2) arr[k++] = rightArr[j++];
    }

public:
    void mergeSort(std::vector<int>& arr, int left, int right) {
        if (left < right) {
            int mid = left + (right - left) / 2; // Prevents overflow

            // Divide phase: Recursively break down the array
            mergeSort(arr, left, mid);
            mergeSort(arr, mid + 1, right);

            // Conquer phase: Merge sorted fragments back together
            merge(arr, left, mid, right);
        }
    }
};

int main() {
    DivideAndConquerEngine engine;
    std::vector<int> dataset = {38, 27, 43, 3, 9, 82, 10};

    std::cout << "--- 1. Divide & Conquer Paradigm (Merge Sort) ---\n";
    std::cout << "Original Dataset: ";
    for (int num : dataset) std::cout << num << " ";
    std::cout << "\n";

    engine.mergeSort(dataset, 0, dataset.size() - 1);

    std::cout << "Sorted Output:   ";
    for (int num : dataset) std::cout << num << " ";
    std::cout << "\n";

    return 0;
}

#include <iostream>
#include <vector>
#include <thread>
#include <algorithm>
#include <iterator>

void merge(std::vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    std::vector<int> L(n1), R(n2);

    std::copy(arr.begin() + left, arr.begin() + mid + 1, L.begin());
    std::copy(arr.begin() + mid + 1, arr.begin() + right + 1, R.begin());

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
        }
    }

    while (i < n1) {
        arr[k++] = L[i++];
    }

    while (j < n2) {
        arr[k++] = R[j++];
    }
}

void parallelMergeSort(std::vector<int>& arr, int left, int right, int depth = 0) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        if (depth < 4) {  // Adjust depth according to the number of cores available
            std::thread leftSorter(parallelMergeSort, std::ref(arr), left, mid, depth + 1);
            std::thread rightSorter(parallelMergeSort, std::ref(arr), mid + 1, right, depth + 1);

            leftSorter.join();
            rightSorter.join();
        } else {
            parallelMergeSort(arr, left, mid, depth + 1);
            parallelMergeSort(arr, mid + 1, right, depth + 1);
        }

        merge(arr, left, mid, right);
    }
}

int main() {
    std::vector<int> arr = {12, 11, 13, 5, 6, 7};
    int arr_size = arr.size();

    std::cout << "Given array is \n";
    for (int i : arr)
        std::cout << i << " ";
    std::cout << std::endl;

    parallelMergeSort(arr, 0, arr_size - 1);

    std::cout << "\nSorted array is \n";
    for (int i : arr)
        std::cout << i << " ";
    std::cout << std::endl;

    return 0;
}

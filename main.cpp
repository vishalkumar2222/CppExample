#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <omp.h>

void merge(std::vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    std::vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; ++i)
        L[i] = arr[left + i];
    for (int i = 0; i < n2; ++i)
        R[i] = arr[mid + 1 + i];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            ++i;
        }
        else {
            arr[k] = R[j];
            ++j;
        }
        ++k;
    }

    while (i < n1) {
        arr[k] = L[i];
        ++i;
        ++k;
    }

    while (j < n2) {
        arr[k] = R[j];
        ++j;
        ++k;
    }
}

void mergeSort(std::vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}



void parallelMergeSort(std::vector<int>& arr, int left, int right, int depth) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        if (depth > 0) {
#pragma omp parallel sections
            {
#pragma omp section
                parallelMergeSort(arr, left, mid, depth - 1);

#pragma omp section
                parallelMergeSort(arr, mid + 1, right, depth - 1);
            }
        }
        else {
            parallelMergeSort(arr, left, mid, 0);
            parallelMergeSort(arr, mid + 1, right, 0);
        }

        merge(arr, left, mid, right);
    }
}

int main() {
    std::ifstream infile("large_unsorted_data_5m.txt");
    std::vector<int> arr;
    std::string line;

    // Reading the data from the file
    while (std::getline(infile, line)) {
        arr.push_back(std::stoi(line));
    }
    infile.close();

    double start_time = omp_get_wtime();

    //int depth = omp_get_max_threads();
    //parallelMergeSort(arr, 0, arr.size() - 1, depth);

	mergeSort(arr, 0, arr.size() - 1);
    
    // Get the ending time
    double end_time = omp_get_wtime();

    // Calculate the duration
    double execution_time = end_time - start_time;

    std::cout << "Execution time: " << execution_time << "\n";

    //std::cout << "Sorted array: ";
    //for (int x : arr) {
    //    std::cout << x << " ";
    //}

    return 0;
}

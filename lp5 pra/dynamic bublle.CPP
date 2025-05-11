
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <omp.h>

using namespace std;

// ------------------------ Sequential Bubble Sort ------------------------
void bubbleSortSequential(vector<int>& arr) {
    int n = arr.size();
    for(int i = 0; i < n-1; ++i) {
        for(int j = 0; j < n-i-1; ++j) {
            if(arr[j] > arr[j+1])
                swap(arr[j], arr[j+1]);
        }
    }
}

// ------------------------ Parallel Bubble Sort ------------------------
void bubbleSortParallel(vector<int>& arr) {
    int n = arr.size();
    for(int i = 0; i < n; i++) {
        #pragma omp parallel for
        for(int j = i % 2; j < n - 1; j += 2) {
            if(arr[j] > arr[j+1])
                swap(arr[j], arr[j+1]);
        }
    }
}

// ------------------------ Merge Function ------------------------
void merge(vector<int>& arr, int l, int m, int r) {
    int i = l, j = m+1, k = 0;
    vector<int> temp(r-l+1);

    while(i <= m && j <= r) {
        if(arr[i] <= arr[j])
            temp[k++] = arr[i++];
        else
            temp[k++] = arr[j++];
    }

    while(i <= m) temp[k++] = arr[i++];
    while(j <= r) temp[k++] = arr[j++];

    for(int i = 0; i < k; i++)
        arr[l + i] = temp[i];
}

// ------------------------ Sequential Merge Sort ------------------------
void mergeSortSequential(vector<int>& arr, int l, int r) {
    if(l < r) {
        int m = (l + r) / 2;
        mergeSortSequential(arr, l, m);
        mergeSortSequential(arr, m+1, r);
        merge(arr, l, m, r);
    }
}

// ------------------------ Parallel Merge Sort ------------------------
void mergeSortParallel(vector<int>& arr, int l, int r) {
    if(l < r) {
        int m = (l + r) / 2;

        #pragma omp parallel sections
        {
            #pragma omp section
            mergeSortParallel(arr, l, m);

            #pragma omp section
            mergeSortParallel(arr, m+1, r);
        }

        merge(arr, l, m, r);
    }
}

// ------------------------ Helper to Copy Arrays ------------------------
vector<int> copyArray(const vector<int>& arr) {
    return vector<int>(arr.begin(), arr.end());
}

// ------------------------ Main Function ------------------------
int main() {
    int n;
    cout << "Enter number of elements: ";
    cin >> n;

    vector<int> arr(n);
    srand(time(0));
    for(int i = 0; i < n; ++i)
        arr[i] = rand() % 1000;

    // Sequential Bubble Sort
    vector<int> arr1 = copyArray(arr);
    double start = omp_get_wtime();
    bubbleSortSequential(arr1);
    double end = omp_get_wtime();
    cout << "Sequential Bubble Sort Time: " << end - start << " seconds\n";

    // Parallel Bubble Sort
    arr1 = copyArray(arr);
    start = omp_get_wtime();
    bubbleSortParallel(arr1);
    end = omp_get_wtime();
    cout << "Parallel Bubble Sort Time: " << end - start << " seconds\n";

    // Sequential Merge Sort
    arr1 = copyArray(arr);
    start = omp_get_wtime();
    mergeSortSequential(arr1, 0, n - 1);
    end = omp_get_wtime();
    cout << "Sequential Merge Sort Time: " << end - start << " seconds\n";

    // Parallel Merge Sort
    arr1 = copyArray(arr);
    start = omp_get_wtime();
    mergeSortParallel(arr1, 0, n - 1);
    end = omp_get_wtime();
    cout << "Parallel Merge Sort Time: " << end - start << " seconds\n";

    return 0;
}


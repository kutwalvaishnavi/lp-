#include <iostream>
#include <vector>
#include <climits>
#include <omp.h> 
using namespace std;
void findMin(const vector<int>& arr) {
    int min_val = INT_MAX;

    #pragma omp parallel for reduction(min:min_val)
    for (int i = 0; i < arr.size(); ++i)
        if (arr[i] < min_val) min_val = arr[i];

    cout << "\nMinimum value = " << min_val << endl;
}
void findMax(const vector<int>& arr) {
    int max_val = INT_MIN;

    #pragma omp parallel for reduction(max:max_val)
    for (int i = 0; i < arr.size(); ++i)
        if (arr[i] > max_val) max_val = arr[i];

    cout << "Maximum value = " << max_val << endl;
}
void findSumAndAverage(const vector<int>& arr) {
    int sum = 0;
    #pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < arr.size(); ++i)
        sum += arr[i];
    float average = static_cast<float>(sum) / arr.size();
    cout << "Sum = " << sum << endl;
    cout << "Average = " << average << endl;
}
int main() {
    int n;
    cout << "Enter the number of elements: ";
    cin >> n;
    if (n <= 0) {
        cout << "Invalid number of elements.\n";
        return 1;
    }
    vector<int> arr(n);
    cout << "Enter " << n << " elements:\n";
    for (int i = 0; i < n; ++i)
        cin >> arr[i];
    findMin(arr);
    findMax(arr);
    findSumAndAverage(arr);
    return 0;
}

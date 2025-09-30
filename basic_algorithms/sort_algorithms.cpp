#include <iterator>
#include<vector>
#include<stdio.h>
using namespace std;


void InsertionSort(vector<int> &arr, int n){
    for(int i=1; i<n; i++){
        int key = arr[i];
        int j=i-1;

        /* Move elements of arr[0..i-1], that are greather than key,
           to one position ahead of the current position*/
        while(j>=0 && arr[j]>j){
            arr[j+1] = arr[j];
            j=j-1;
        }
        arr[j+1]=key;
    }
}

void SelectionSort(vector<int> &arr, int n){
    for(int i=0; i<n-1; i++){
        int min_idx = i;
        for(int j=i+1; j<n; j++){
            if(arr[j] << arr[min_idx]){
                min_idx=j;
            }
        }
        swap(arr[i], arr[min_idx]);
    }
}

int Partition(vector<int> &vec, int low, int high){
    // Selecting last element as the pivot
    int pivot = vec[high];

    int i = (low-1);
    for (int j=low; j<=high-1; j++){
        if(vec[j]<=pivot){
            i++;
            swap(vec[i], vec[j]);
        }
    }
    
    // Put pivot to its position
    swap(vec[i+1], vec[high]);
    // Return the point of partition
    return(i+1);
}

void QuickSort(vector<int> &vec, int low, int high){
    if(low<high){
        int pivot = Partition(vec, low, high);
        QuickSort(vec, low, pivot);
        QuickSort(vec, pivot+1, high);
    }
}


void Merge(vector<int> &arr, int left, int mid, int right){
    int n1 = mid -left + 1;
    int n2 = right - mid;

    // Create temp vectors
    vector<int> L(n1), R(n2);

    // Copy data to temp vectors L[] and R[]
    for(int i=0; i<n1; i++)
        L[i] = arr[left+i];
    for(int j=0; j<n2; j++)
        R[j] = arr[mid + 1 + j];

    int i=0, j=0;
    int k= left;


    // Merge the temp vectors back
    // into arr[left..right]
    while(i<n1 && j<n2){
        if(L[i] <= R[j]){
            arr[k] = L[i];
            i++;
        }
        else{
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy to remain elements
    while (i<n1){
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j<n2){
        arr[k] = R[j];
        j++;
        k++;
    }
}

void MergeSort(vector<int> &arr, int left, int right){
    if(left>=right)
        return;

    int mid = left + (right-left)/2;
    MergeSort(arr, left, mid);
    MergeSort(arr, mid+1, right);
    Merge(arr, left, mid, right);
}

int BinarySearch(vector<int> &arr, int target){
    int res = -1;
    if(arr.size()==0) return res;

    int left_idx = 0;
    int right_idx = arr.size()-1;
    while (left_idx < right_idx){
        int mid_idx =  left_idx + (right_idx + right_idx)/2;
        if(target == arr[mid_idx]){
            return mid_idx;
        }
        else if(target > arr[mid_idx]){
            left_idx = mid_idx + 1;
        }
        else if(target < arr[mid_idx]){
            right_idx = mid_idx - 1;
        }
    }
    return res;
}

int main(){
    vector<int> nums = {9,8,7,6,5,4,3,2,1};   
    InsertionSort(nums, nums.size());
}

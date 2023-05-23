#include<iostream>
#include<omp.h>
#include<bits/stdc++.h>

using namespace std;

void sequential_bubble_sort(int arr[], int size) {
    int array[size];
    for(int i = 0; i < size; i++) {
        array[i] = arr[i];
    }

    double start = omp_get_wtime();
    for(int i = 0; i < size - 1; i++) {
        for(int j = 0; j < size - i - 1; j++) {
            if(array[j] > array[j+1]) {
                swap(array[j], array[j+1]);
            }
        }
    }
    double end = omp_get_wtime();

    cout << "Sequential Bubble Sort:" << endl;
    for(int i = 0; i < size; i++) {
        cout << array[i] << " ";
    }
    cout << endl;
    cout << "Time Required: " << end - start << " seconds" << endl;
    cout << endl;
}

void parallel_bubble_sort(int arr[], int size) {
    int array[size];
    for(int i = 0; i < size; i++) {
        array[i] = arr[i];
    }
    double start = omp_get_wtime();
    for(int k = 0; k < size; k++) {
        if(k % 2 == 0) {
            #pragma omp parallel for
            for(int i = 1; i < size - 1; i += 2) {
                if(array[i] > array[i+1]) {
                    swap(array[i], array[i+1]);
                }
            }
        }
        else {
            #pragma omp parallel for
            for(int i = 0; i < size - 1; i += 2) {
                if(array[i] > array[i+1]) {
                    swap(array[i], array[i+1]);
                }
            }
        }
    }
    double end = omp_get_wtime();

    cout << "Parallel Bubble Sort:" << endl;
    for(int i = 0; i < size; i++) {
        cout << array[i] << " ";
    }
    cout << endl;
    cout << "Time Required: " << end - start << " seconds" << endl;
    cout << endl;
}

void merge(int array[], int low, int mid, int high, int size) {
    int temp[size];
    int i = low;
    int j = mid + 1;
    int k = 0;
    while((i <= mid) && (j <= high)) {
        if(array[i] >= array[j]) {
            temp[k] = array[j];
            k++;
            j++;
        }
        else {
            temp[k] = array[i];
            k++;
            i++;
        }
    }
    while(i <= mid) {
        temp[k] = array[i];
        k++;
        i++;
    }
    while(j <= high) {
        temp[k] = array[j];
        k++;
        j++;
    }

    k = 0;
    for(int i = low; i <= high; i++) {
        array[i] = temp[k];
        k++;
    }
}

void mergesort(int array[], int low, int high, int size) {
    if(low < high) {
        int mid = (low + high) / 2;
        mergesort(array, low, mid, size);
        mergesort(array, mid + 1, high, size);
        merge(array, low, mid, high, size);
    }
}

void perform_merge_sort(int arr[], int size) {
    int array[size];
    for(int i = 0; i < size; i++) {
        array[i] = arr[i];
    }
    double start = omp_get_wtime();
    mergesort(array, 0, size - 1, size);
    double end = omp_get_wtime();

    cout << "Merge Sort:" << endl;
    for(int i = 0; i < size; i++) {
        cout << array[i] << " ";
    }
    cout << endl;
    cout << "Time Required: " << end - start << " seconds" << endl;
    cout << endl;
}

void p_mergesort(int array[], int low, int high, int size) {
    if(low < high) {
        int mid = (low + high) / 2;
        #pragma omp parallel sections
        {
            #pragma omp section
            p_mergesort(array, low, mid, size);
            #pragma omp section
            p_mergesort(array, mid + 1, high, size);
        }
        merge(array, low, mid, high, size);
    }
}

void perform_p_merge_sort(int arr[], int size) {
    int array[size];
    for(int i = 0; i < size; i++) {
        array[i] = arr[i];
    }
    double start = omp_get_wtime();
    p_mergesort(array, 0, size - 1, size);
    double end = omp_get_wtime();

    cout << "Parallel Merge Sort:" << endl;
    for(int i = 0; i < size; i++) {
        cout << array[i] << " ";
    }
    cout << endl;
    cout << "Time Required: " << end - start << " seconds" << endl;
    cout << endl;
}

int main(int argc, char const *argv[]) {
    int SIZE;
    int MAX = 1000;
    cout << "Enter size of array: ";
    cin >> SIZE;

    int array[SIZE];
    for(int i = 0; i < SIZE; i++) {
        array[i] = rand() % MAX;
    }

    cout << "Initial Array:" << endl;
    for(int i = 0; i < SIZE; i++) {
        cout << array[i] << " ";
    }
    cout << endl << endl;

    sequential_bubble_sort(array, SIZE);
    parallel_bubble_sort(array, SIZE);
    perform_merge_sort(array, SIZE);
    perform_p_merge_sort(array, SIZE);

    return 0;
}

/*

Enter size of array: 30
Initial Array:
41 467 334 500 169 724 478 358 962 464 705 145 281 827 961 491 995 942 827 436 391 604 902 153 292 382 421 716 718 895 

Sequential Bubble Sort:
41 145 153 169 281 292 334 358 382 391 421 436 464 467 478 491 500 604 705 716 718 724 827 827 895 902 942 961 962 995 
Time Required: 0 seconds

Parallel Bubble Sort:
41 145 153 169 281 292 334 358 382 391 421 436 464 467 478 491 500 604 705 716 718 724 827 827 895 902 942 961 962 995 
Time Required: 0.00499988 seconds

Merge Sort:
41 145 153 169 281 292 334 358 382 391 421 436 464 467 478 491 500 604 705 716 718 724 827 827 895 902 942 961 962 995 
Time Required: 0 seconds

Parallel Merge Sort:
41 145 153 169 281 292 334 358 382 391 421 436 464 467 478 491 500 604 705 716 718 724 827 827 895 902 942 961 962 995 
Time Required: 0.000999928 seconds


*/
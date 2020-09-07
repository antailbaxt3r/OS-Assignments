#include "sort.h"
#include <stdio.h>

void exchange(int *a, int *b){
    int c = *b;
    *b = *a;
    *a = c;
}

int partition (int arr[], int low, int high){ 
    int pivot = arr[high];
    int i = (low - 1);
    for (int j = low; j <= high- 1; j++){ 
        if (arr[j] < pivot){ 
            i++; 
            swap(&arr[i], &arr[j]); 
        } 
    } 
    exchange(&arr[i + 1], &arr[high]); 
    return (i + 1); 
} 

void sort(int arr[], int start, int size){ 
    if (start < size){
        int i = partition(arr, start, size); 
        sort(arr, start, i-1); 
        sort(arr, i+1, size); 
    } 
} 
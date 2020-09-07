#include "sort.h"
#include <stdio.h>

void sort(int arr[], int start,  int n){ 
    int i, j;
    int k; 
    for (i = 1; i < n; i++) { 
        k = arr[i]; 
        j = i - 1;
        while (j >= 0 && arr[j] > k) { 
            arr[j+1] = arr[j]; 
            j = j - 1; 
        } 
        arr[j + 1] = k; 
    } 
} 
#include "sort.h"
#include <stdio.h>

void exchange(int *a, int *b){
    int c = *b;
    *b = *a;
    *a = c;
}

void sort(int arr[], int start, int n){
    int i, j;
    for (i = 0; i < n - 1; i++){
        for (j = 0; j < n - i - 1; j++){
            if (arr[j] > arr[j + 1]) exchange(&arr[j], &arr[j + 1]);
        }
    }
}
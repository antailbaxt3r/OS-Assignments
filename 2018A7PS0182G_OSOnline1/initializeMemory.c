#include "memInterface.h"
#include <stdio.h>
#include <stdlib.h>

int initializeMemory(FILE *fp, int BobMem[], int k){
    char n[1000];
    int count = 0;

    while(fgets(n, 1000, fp) != NULL) {
        int t = atoi(n);
        BobMem[count++] = t;
    }
    int temp = count;
    while(count < k){
        BobMem[count++] = -1;
    }
    return temp;
}
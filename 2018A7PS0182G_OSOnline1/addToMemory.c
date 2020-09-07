#include "memInterface.h"
#include <stdio.h>
#include <stdlib.h>
#include<stdbool.h>  

void addToMemory(int BobMem[], struct Result *res, int k, int num){
    bool flag = false;
    for(int i = 0; i < k; i++){
        if(BobMem[i] == num) {
            flag = true;
            break;
        }
    }
    if(!flag){
        for(int i = k-1; i > 0; i--){
            BobMem[i] = BobMem[i-1];
        }
        BobMem[0] = num;
    }
    if(flag){
        res->score = res->score + 1;
    }
    res->attempts = res->attempts + 1;
}
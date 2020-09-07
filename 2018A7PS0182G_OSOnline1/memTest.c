#include "memInterface.h"
#include <stdio.h>
#include <stdlib.h>

struct Result memTest(FILE *fp1, FILE *fp2, int BobMem[], int k){
    struct Result res;
    res.attempts = 0;
    res.score = 0;
    char q[1000];
    while(fgets(q, 1000, fp1) != NULL) {
        int t = atoi(q);
        if(t == 1){
            int num = atoi(q+2);
            addToMemory(BobMem, &res, k, num);
        }else if(t == 2){
            printMemoryStats(fp2, BobMem, res, k);
        }else if(t == 3){
            printScore(fp2, res);
        }else{
            fprintf(fp2, "Last attempt number was:%d Error[queryHandler fails]:Unknown Query Type.\n", res.attempts);
        }
    }
    fprintf(fp2, "Final Score: %d and Attempts: %d", res.score, res.attempts);
}
#include "memInterface.h"
#include <stdio.h>
#include <stdlib.h>

void printMemoryStats(FILE *fp2, int BobMem[], struct Result res, int k){
    fprintf(fp2, "Last attempt was: %d\nCurrent state is:", res.attempts);
    for(int i = 0; i < k; i++){
        fprintf(fp2, "%d ", BobMem[i]);
    }
    fprintf(fp2, "\n");
}
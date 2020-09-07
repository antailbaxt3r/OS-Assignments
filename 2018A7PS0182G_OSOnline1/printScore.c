#include "memInterface.h"
#include <stdio.h>
#include <stdlib.h>

void printScore(FILE *fp2, struct Result res){
    fprintf(fp2, "Current Score: %d and Attempts: %d\n", res.score, res.attempts);
}
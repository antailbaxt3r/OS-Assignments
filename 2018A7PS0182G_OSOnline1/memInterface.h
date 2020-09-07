#ifndef _MEM_HEADER
#define _MEM_HEADER
#include <stdio.h>
//function definitions
struct Result {
    int score;
    int attempts;
};
extern int initializeMemory(FILE *fp, int BobMem[], int k);
extern struct Result memTest(FILE *fp1, FILE *fp2, int BobMem[], int k);
extern void printScore(FILE *fp2, struct Result res);
extern void printMemoryStats(FILE *fp2, int BobMem[], struct Result res, int k);
extern void addToMemory(int BobMem[], struct Result *res, int k, int num);
#endif
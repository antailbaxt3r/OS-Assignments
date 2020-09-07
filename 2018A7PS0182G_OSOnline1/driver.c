#include "memInterface.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    int k;
    k =  atoi(argv[2]);
    if(k < 2 || k > 5){
        printf("ERROR");
        exit(1);
    }
    int BobMem[k];

    FILE * fp = fopen(argv[1], "r");
    FILE * fp1 = fopen(argv[3], "r");
    FILE * fp2 = fopen(argv[4], "w");

    int count = initializeMemory(fp, BobMem, k);
    // printf("%d\n", count);
    // for(int i = 0; i < k; i++){
    //     printf("%d\n", BobMem[i]);
    // }
    struct Result res = memTest(fp1, fp2, BobMem, k);

}
#include "sort.h"
#include <stdio.h>

int main(int argc, char* argv[]){

    FILE * input = fopen(argv[1], "r");
    //Read number of elements
    int n;
    fscanf(input, "%d", &n);
    //Read elements
    int a[n];
    for(int i = 0; i < n; i++){
        fscanf(input, "%d", &a[i]);
    }
    fclose(input);
    //Sort
    sort(a, 0, n);

    //Save to output file
    char filename[15];
    printf("Enter name of output file: \n");
    scanf("%s", filename);
    
    FILE * output = fopen(filename, "w");
    for(int i = 0; i < n; i++){
        fprintf(output, "%d ", a[i]);
    }
    fclose(output);
}
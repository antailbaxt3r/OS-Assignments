#include<pthread.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<asm/unistd.h>

int l1, l2;
int *a, *b ,*c;

void *calculate(void *param){
    long unsigned int n = (long unsigned int) param;
    long unsigned int sum = 0;
    int j = n;
    for(int i = 0; i <= n; i++){
        if(j < l2 && j >= 0 && n>=0 && i < l1){
            sum += a[i] * b[j];
        }
        j--;
    }
    pthread_exit((void *)sum);
}

int main(int argc, char *argv[]){
    int n1 = atoi(argv[1]);
    int n2 = atoi(argv[2]);
    l1 = 0, l2 = 0;

    //count lengths
    int t = n1;
    while(t!=0){
        t/=10;
        l1++;
    }
    t = n2;
    while(t!=0){
        t/=10;
        l2++;
    }
    a = (int *) malloc(l1 * sizeof(int));
    b = (int *) malloc(l2 * sizeof(int));
    c = (int *) malloc((l1+l2-1) * sizeof(int));

    //convert to int arrays
    for(int i = 0; i < l1; i++) a[i] = 0;
    for(int i = 0; i < l2; i++) b[i] = 0;
    t = n1;
    for(int i = l1-1; i >= 0; i--) {
        int x = t%10;
        a[i] = x;
        t /= 10;
    }
    t = n2;
    for(int i = l2-1; i >= 0; i--) {
        int x = t%10;
        b[i] = x;
        t /= 10;
    }

    //thread control
    pthread_t tid[l1+l2-1];
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    for(long unsigned int i = 0; i < l1+l2-1; i++){
        pthread_create(&tid[i], &attr, calculate, (void *) i);
    }
    for(int i = 0; i < l1+l2-1; i++){
        pthread_join(tid[i], (void *)&c[i]);
    }
    
    int res[l1+l2];
    for(int i = 0; i < l1+l2; i++)res[i] = 0;
    for(int i = l1+l2-2; i >= 0; i--){
        int x = c[i];
        res[i+1] += x%10;
        int q = x/10;
        if(i!=0){
            c[i-1] += q;
        }else{
            res[i] += q;
        }
    }

    long unsigned int product = 0;
    long unsigned int tens = 1;
    for(int i = l1+l2-1; i >= 0; i--){
        product += res[i] * tens;
        tens *= 10;
    }
    printf("%lu\n", product);
}
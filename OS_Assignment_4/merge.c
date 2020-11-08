#include<pthread.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<asm/unistd.h>

int n, m, lastBIndex = 0, lastAIndex = 0;
int *a, *b, *result;

void *findPositionA(void * param){
    long unsigned int index = (long unsigned int) param;
    int x = a[index];
    long unsigned int fi = 0;
    if(x < b[0]){
        fi = index;
    }else if (x > b[m-1]){
        fi = m+index;
    }else{
        for(int j = 0; j < m-1; j++){
            if(x > b[j] && x < b[j+1]){
                fi = index+j+1;
                break;
            }
        }
    }
    result[fi] = x;
    pthread_exit((void *) fi);
}

void *findPositionB(void * param){
    long unsigned int index = (long unsigned int) param;
    int x = b[index];
    long unsigned int fi = 0;
    if(x < a[0]){
        fi = index;
    }else if (x > a[n-1]){
        fi = n+index;
    }else{
        for(int j = lastAIndex; j < n-1; j++){
            if(x > a[j] && x < a[j+1]){
                fi = index+j+1;
                break;
            }
        }
    }
    result[fi] = x;
    pthread_exit((void *) fi);
}

int main(){
    scanf("%d %d", &n, &m);
    a = (int *) malloc(n * sizeof(int));
    b = (int *) malloc(m * sizeof(int));
    result = (int *) malloc((n+m) * sizeof(int));

    for(int i = 0; i < n; i++) scanf("%d", &a[i]);
    for(int i = 0; i < m; i++) scanf("%d", &b[i]);
    for(int i = 0; i < m+n; i++) result[i] = 0;

    //thread control
    pthread_t tid[m+n];
    pthread_attr_t attr;
    pthread_attr_init(&attr);

    for(long unsigned int i = 0; i < n; i++){
        pthread_create(&tid[i], &attr, findPositionA, (void *)i);
    }
    for(long unsigned int i = 0; i < m; i++){
        pthread_create(&tid[n+i], &attr, findPositionB, (void *)i);
    }

    for(int i = 0; i < n+m; i++){
        pthread_join(tid[i], NULL);
    }
    for(int i = 0; i < m+n; i++){
        printf("%d ", result[i]);
    }
    printf("\n");
}
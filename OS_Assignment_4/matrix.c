#include<pthread.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<asm/unistd.h>

int m, k, n;
int **a, **b, **c;

void *calulate(void * pnt){
    int *x = (int *)pnt;
    int row = x[0], col = x[1];
    long unsigned int sum = 0;
    for(int i = 0; i < k; i++){
        sum += a[row][i] * b[i][col];
    }
    pthread_exit((void *)sum);
}

int main(int argc, char argv[]){

    //initialization nad inputs
    scanf("%d", &m);
	scanf("%d", &k);
	scanf("%d", &n);
    a = (int **) malloc(m * sizeof(int));
    b = (int **) malloc(k * sizeof(int));
    c = (int **) malloc(m * sizeof(int));

    for(int i = 0; i < m; i++){
        a[i] = (int *) malloc(k * sizeof(int));
    }
    for(int i = 0; i < k; i++){
        b[i] = (int *) malloc(n * sizeof(int));
    }
	for(int i=0; i<m; i++){
		c[i]= (int *) malloc(n*sizeof(int));
	}

    for(int i=0; i<m; i++){
		for (int j=0; j<k; j++){
			scanf("%d", &a[i][j]);
		}
	}
	for(int i=0; i<k; i++){
		for (int j=0; j<n; j++){
			scanf("%d", &b[i][j]);
		}
	}
    for(int i = 0; i < m; i++)
        for(int j = 0; j < n; j++) c[i][j] = 0;

    //thread control
    pthread_t tid[m][n];
    pthread_attr_t attr;
    pthread_attr_init(&attr);

    for(int i = 0; i < m; i++)
        for(int j = 0; j < n; j++){
            int *x= (int *) malloc(2 * sizeof(int));
            x[0] = i;
            x[1] = j;
            pthread_create(&tid[i][j], &attr, calulate, (void *)x);
        }

    for(int i = 0; i < m; i++)
        for(int j = 0; j < n; j++)
            pthread_join(tid[i][j], (void **)&c[i][j]);

    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            printf("%d ", c[i][j]);
        }
        printf("\n");
    }
    return 0;
}

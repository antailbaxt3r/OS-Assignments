#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>

char ** grid;
int n = 4;
int m = 4;
int flag = 0;

// int go(int parent_id){
//     int i = 0, j = 0;
//     // int pid = getpid();
//     // int c;
//     // if(i < n-1)
//     //     if(grid[i+1][j] == '0'){
//     //         pid = fork();
//     //         if(!pid){
//     //             c = go(i+1, j);
//     //             exit(0);
//     //         }
//     //     }

//     // if(pid)
//     //     if(j < n-1)
//     //         if(grid[i][j+1] == '0'){
//     //             pid = fork();
//     //             if(!pid){
//     //                 c = go(i, j+1);
//     //                 exit(0);
//     //             }
//     //         }

//     // if(pid){
//     //     while(wait(NULL) != -1);
//     //     if(c){
//     //         if(i == n-1 && j == m-1){
//     //             printf("(%d, %d) ", i, j);
//     //         }else if(c) printf("-> (%d, %d) ", i, j);
//     //         return 1;
//     //     }else return 0;
//     // }
    
    
// }

int main(){
    grid = malloc(4 * 4 * sizeof(int));
    grid[0] = "0010";
    grid[1] = "1001";
    grid[2] = "1010";
    grid[3] = "1000";
    
    int i = 0, j = 0;
    int parent_id = getpid();
    int success = 0;

    while(!flag){
        int right=1, down=1;
        if(j < m-1) down = fork();
        if(!down){
            j++;
            if(i == n-1 && j == m-1){
                printf("(%d, %d) ", i, j);
                exit(1);
            }
            if(grid[i][j] == '0') {
                continue;
            }else exit(0);
        }else if(i < n-1) right = fork();

        if(!right){
            i++;
            if(i == n-1 && j == m-1){
                printf("(%d, %d) ", i, j);
                exit(1);
            }
            if(grid[i][j] == '0') {
                continue;
            }else exit(0);
        }
    
        if(right && down){
            int s1, s2;
            wait(&s1);
            wait(&s2);
            if(!(s1 == 256 || s2 == 256)){
                if(getpid() != parent_id){
                    return 0;
                }else {
                    flag = 1;
                    success = 0;
                }
            }else {
                if(getpid() != parent_id){
                    printf("-> (%d, %d) ", i, j);
                    return 1;
                }else {
                    flag = 1;
                    success = 1;
                }
            }
        }
        
    }

    if(success)printf("\nMJ found\n");
    else printf("\nNot Found\n");
}
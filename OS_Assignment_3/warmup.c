#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>


void tree(int start, int end, int levels){
    if(levels == 0) return;
    pid_t id;
    for(int i = start; i < end; i++){
        id = fork();
        if(!id){
            kill(getpid(), SIGSTOP);
            tree((i*(i-1))/2+1,(i*(i-1))/2+1+i,levels-1);
            printf("(EXITING) my ID is %d and my parent ID is: %d\n", getpid(), getppid());
            exit(0);
        }
    }
    if(id){
        int child, status;
        while((child = waitpid(-1, &status, WUNTRACED)) != -1){
            if(WIFSTOPPED(status)) {
                kill(child, SIGCONT);
            }
        }
        while(wait(NULL)!=-1);
        printf("(EXITING) my ID is: %d and my parent ID is: %d\n",getpid(),getppid());
    }
    exit(0);
}

int main(int argc, char *argv[]){
    int num=argv[1][0]-'0';
	int levels=argv[2][0]-'0';
	tree(1,num+1,levels);
    return 0;
}
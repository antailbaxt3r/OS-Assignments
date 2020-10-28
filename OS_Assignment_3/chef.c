#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>

struct chef {
    int pid;
    int batch;
    int time;
    int complete;
    int collected;
    int childCount;
    int children[10];
    int cpids[10];
};
struct memory {
    struct chef chefs[20];
};
struct memory * mem;
int n;

void stopWork(int id){
    for(int i = 0; i < mem->chefs[id].childCount; i++)
        stopWork(mem->chefs[id].children[i]);
    kill(mem->chefs[id].pid, SIGKILL);
}


void cook(int id){
    mem->chefs[id].pid = getpid();
    for(int i = 0; i < mem->chefs[id].childCount; i++){
        int p = fork();
        if(p==0){
            cook(mem->chefs[id].children[i]);
        }else{
            mem->chefs[id].cpids[i] = p;
        }
    }
    sleep(mem->chefs[id].time);
    printf("i am process %d and i woke up.\n",id);
    mem->chefs[id].complete = 1;
    for(int i = 0; i < mem->chefs[id].childCount; i++){
        int c = mem->chefs[id].children[i];
        if(mem->chefs[c].complete){
            printf("%d % d\n", mem->chefs[c].batch, mem->chefs[c].collected);
            mem->chefs[id].collected += mem->chefs[c].batch;
            mem->chefs[id].collected += mem->chefs[c].collected;
        }
        int ret = waitpid(mem->chefs[id].cpids[i], NULL, WNOHANG);
        if(ret == 0) stopWork(c);
    }
    if(id) exit(0);
}

void main(){
    scanf("%d", &n);
    int shmid = shmget(IPC_PRIVATE, sizeof(struct memory), 0666 | IPC_CREAT);
    mem = shmat(shmid, 0, 0);
    for(int i = 0; i < n; i++){
        mem->chefs[i].childCount = 0;
        mem->chefs[i].collected = 0;
        mem->chefs[i].complete = 0;
    }
    for(int i = 0; i < n-1; i++){
        int c, s;
        scanf("%d %d", &c, &s);
        mem->chefs[c-1].children[mem->chefs[c-1].childCount] = s-1;
        mem->chefs[c-1].childCount++;
    }
    for(int i = 0; i < n; i++){
		int temp;
		scanf("%d",&temp);
		mem->chefs[i].batch = temp;
	}
    for(int i = 0; i < n; i++){
		int temp;
		scanf("%d",&temp);
		mem->chefs[i].time = temp;
	}

    cook(0);

    for(int i = 0; i < n; i++){
        struct chef c = mem->chefs[i];
        printf("Chef#%d: #dishes made : %d #dishes collected : %d\n", i, c.batch, c.collected);
    }
    printf("Worthy Dishes : %d\n", mem->chefs[0].collected + mem->chefs[0].batch);

}
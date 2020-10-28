#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>
#include <signal.h>
#include "cricket.h"

int main(){
    int shmid = shmget(IPC_PRIVATE, sizeof(struct memory), 0666 | IPC_CREAT);
    mem = shmat(shmid, 0, 0);

    int pid = fork();
    if (!pid) {
        //umpire process
        mem->ump_pid = getpid();
        init_ump();
        int batting_team;
        int toss_result = toss();
        if (toss_result) {
            mem->team1.batting = 1;
            mem->team2.batting = 0;
            batting_team = 1;
        } else {
            mem->team1.batting = 0;
            mem->team2.batting = 1;
            batting_team = 2;
        }
        int runs = 0, wickets = 0, balls = 0;
        while(mem->overs < mem->max_overs){
            (batting_team == 1) ? kill(mem->team2.bwpid, SIGRTMIN+1) : kill(mem->team1.bwpid, SIGRTMIN+1);
            mem->balls++;
            signal(SIGRTMIN+2, shot_hit());
            int res = mem->curr_res;    
            if(res == 7) {
                send_out();
                wickets++;
            }else {
                runs += res;
                add_to_striker(res);
            }
            balls++;
            if(balls % 6 == 0){
                mem->overs++;
            }
            if(wickets == 10 || mem->overs == mem->max_overs){
                innings_over();
                break;
            }
        }

        while(mem->overs < mem->max_overs){
            (batting_team == 1) ? kill(mem->team2.bwpid, SIGRTMIN+1) : kill(mem->team1.bwpid, SIGRTMIN+1);
            mem->balls++;
            signal(SIGRTMIN+2, shot_hit());
            int res = mem->curr_res;
            if(res == 7) {
                send_out();
                wickets++;
            }else {
                runs += res;
                add_to_striker(res);
            }
            balls++;
            if(balls == 6){
                mem->overs++;
                over_change();
            }
            if(wickets == 10 || mem->overs == mem->max_overs || runs >= mem->target){
                innings_over();
                break;
            }
        }
        
    } else {
        int pid_ = fork();
        if (!pid_) {
            //team1
            init_team1();
            if(mem->team1.batting){
                //create 2 batting processes
                int b = fork();
                if(!b){
                    //batsman1
                    mem->team1.b1pid = getpid();
                    mem->team1.b1id = 0;
                    mem->team1.players[mem->team1.b1id].on_strike = 1;
                    while(mem->overs < mem->max_overs && mem->team1.players[mem->team1.b1id].on_strike){
                        kill(mem->ump_pid, SIGRTMIN+2);
                        signal(SIGRTMIN+3, runs_hit());
                        signal(SIGRTMIN+5, out());
                    }
                } else {
                    int b_ = fork();
                    if(!b_){
                        //batsman2
                        mem->team1.b2pid = getpid();
                        mem->team1.b2id = 1;
                        mem->team1.players[mem->team1.b2id].on_strike = 0;
                    }
                }
            }else {
                //create 1 bolwer process
                int bw = fork();
                if(!bw){
                    //bowler
                    mem->team1.bwpid = getpid();
                    mem->team1.bwid = 0;
                }
            }
        } else {
            //team2
            init_team2();
            if(mem->team2.batting){
                //create 2 batting processes
                int b = fork();
                if(!b){
                    //batsman1
                    mem->team2.b1pid = getpid();
                    mem->team2.b1id = 0;
                    mem->team2.players[mem->team2.b1id].on_strike = 1;
                    
                } else {
                    int b_ = fork();
                    if(!b_){
                        //batsman2
                        mem->team2.b2pid = getpid();
                        mem->team2.b2id = 1;
                        mem->team2.players[mem->team2.b2id].on_strike = 0;
                    }
                }
            }else {
                //create 1 bolwer process
                int bw = fork();
                if(!bw){
                    //bowler
                    mem->team2.bwpid = getpid();
                    mem->team2.bwid = 0;
                }
            }
        } 
    }

    while(wait(NULL) != -1);
    write_to_files();
}
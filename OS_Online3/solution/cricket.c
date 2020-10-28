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

//INITIALIZE MEMORY
void init_ump(){
    FILE *ump;
    ump = fopen("umpire.txt","r");
    //umpire
    int t;
    fscanf(ump, "%d", &mem->ump_seed);
    fscanf(ump, "%d", &mem->max_overs);
}

void init_team1(){
    FILE *team1ptr;
    team1ptr = fopen("team1.txt","r");

    //team1
    char temp[20];
    fgets(temp, 20, team1ptr);
    mem->team1.name = temp;
    fscanf(team1ptr, "%d\n", &mem->team1.seed);
    for(int i = 0; i < 11; i++){
        fgets(temp, 20, team1ptr);
        mem->team1.players[i].name = temp;
        mem->team1.players[i].runs = 0;
        mem->team1.players[i].balls_bowled = 0;
        mem->team1.players[i].balls_played = 0;
        mem->team1.players[i].status = "NOT PLAYED";
        mem->team1.players[i].runs_given = 0;
        mem->team1.players[i].on_strike = 0;
        mem->team1.players[i].bowling = 0;
    }
    for(int i = 0; i < 11; i++){
        fscanf(team1ptr, "%d", &mem->team1.players[i].seed);
    }
}

void init_team2(){
    FILE *team2ptr;
    team2ptr = fopen("team2.txt","r");

    //team2
    char temp[20];
    fgets(temp, 20, team2ptr);
    mem->team2.name = temp;
    fscanf(team2ptr, "%d\n", &mem->team2.seed);
    for(int i = 0; i < 11; i++){
        fgets(temp, 20, team2ptr);
        mem->team2.players[i].name = temp;
        mem->team2.players[i].runs = 0;
        mem->team2.players[i].balls_bowled = 0;
        mem->team2.players[i].balls_played = 0;
        mem->team2.players[i].status = "NOT PLAYED";
        mem->team2.players[i].runs_given = 0;
        mem->team2.players[i].on_strike = 0;
        mem->team2.players[i].bowling = 0;
    }
    for(int i = 0; i < 11; i++){
        fscanf(team2ptr, "%d", &mem->team2.players[i].seed);
    }
}

//TOSS COIN

int toss(){
    srand(mem->ump_seed);
    return rand() % 2;
}

int runs_hit(){
    srand(mem->ump_seed);
    int res = rand() % 8;
    mem->curr_res = res;
    return res;
}

int shot_hit(){
    if(mem->team1.batting == 1){
        if(mem->team1.players[mem->team1.b1id].on_strike){
            kill(mem->team1.b1pid, SIGRTMIN+3);
        }else{
            kill(mem->team1.b2pid, SIGRTMIN+3);
        }
    }else {
        if(mem->team2.players[mem->team2.b1id].on_strike){
            kill(mem->team2.b1pid, SIGRTMIN+3);
        }else{
            kill(mem->team2.b2pid, SIGRTMIN+3);
        }
    }
    return 0;
}

void send_out(){
    if(mem->team1.batting == 1){
        if(mem->team1.players[mem->team1.b1id].on_strike){
            kill(mem->team1.b1pid, SIGRTMIN+5);
        }else{
            kill(mem->team1.b2pid, SIGRTMIN+5);
        }
        mem->team2.players[mem->team2.bwid].wickets++;
    }else {
        if(mem->team2.players[mem->team2.b1id].on_strike){
            kill(mem->team2.b1pid, SIGRTMIN+5);
        }else{
            kill(mem->team2.b2pid, SIGRTMIN+5);
        }
        mem->team1.players[mem->team1.bwid].wickets++;
    }
};

void add_to_striker(int res){
    int strike_change = 0;
    if(res%2 != 0) strike_change = 1;
    if(mem->team1.batting == 1){
        if(mem->team1.players[mem->team1.b1id].on_strike){
            mem->team1.players[mem->team1.b1id].runs += res;
            mem->team1.players[mem->team1.b1id].balls_played++;
            if(strike_change){
                mem->team1.players[mem->team1.b1id].on_strike = 0;
                mem->team1.players[mem->team1.b2id].on_strike = 1;
            }
        }else{
            mem->team1.players[mem->team1.b2id].runs += res;
            mem->team1.players[mem->team1.b2id].balls_played++;
            if(strike_change){
                mem->team1.players[mem->team1.b1id].on_strike = 1;
                mem->team1.players[mem->team1.b2id].on_strike = 0;
            }
        }
    }else {
        if(mem->team2.players[mem->team2.b1id].on_strike){
            mem->team2.players[mem->team2.b1id].runs += res;
            mem->team2.players[mem->team2.b1id].balls_played++;
            if(strike_change){
                mem->team2.players[mem->team2.b1id].on_strike = 0;
                mem->team2.players[mem->team2.b2id].on_strike = 1;
            }
        }else{
            mem->team2.players[mem->team2.b2id].runs += res;
            mem->team2.players[mem->team2.b2id].balls_played++;
            if(strike_change){
                mem->team2.players[mem->team2.b1id].on_strike = 1;
                mem->team2.players[mem->team2.b2id].on_strike = 0;
            }
        }
    }
}

void innings_over(){
    if(mem->team1.batting == 1){
        kill(mem->team1.b1pid, SIGRTMIN+9);
        kill(mem->team1.b2pid, SIGRTMIN+9);
        kill(mem->team2.bwpid, SIGRTMIN+9);
    }else {
        kill(mem->team2.b1pid, SIGRTMIN+9);
        kill(mem->team2.b2pid, SIGRTMIN+9);
        kill(mem->team1.bwpid, SIGRTMIN+9);
    }
    mem->overs = 0;
}

void over_change(){
    int strike_change = 1;
    if(mem->team1.batting == 1){
        if(mem->team1.players[mem->team1.b1id].on_strike){
            if(strike_change){
                mem->team1.players[mem->team1.b1id].on_strike = 0;
                mem->team1.players[mem->team1.b2id].on_strike = 1;
            }
        }else{
            if(strike_change){
                mem->team1.players[mem->team1.b1id].on_strike = 1;
                mem->team1.players[mem->team1.b2id].on_strike = 0;
            }
        }
    }else {
        if(mem->team2.players[mem->team2.b1id].on_strike){
            if(strike_change){
                mem->team2.players[mem->team2.b1id].on_strike = 0;
                mem->team2.players[mem->team2.b2id].on_strike = 1;
            }
        }else{
            if(strike_change){
                mem->team2.players[mem->team2.b1id].on_strike = 1;
                mem->team2.players[mem->team2.b2id].on_strike = 0;
            }
        }
    }
}

void out(){
    if(mem->team1.batting == 1){
        if(mem->team1.players[mem->team1.b1id].on_strike){
           for(int i = mem->team1.b1id; i < 11; i++){
               if(mem->team1.players[i].status == "NOT PLAYED"){
                   mem->team1.b1id = i;
                   mem->team1.players[i].status = "NOT OUT";
                   mem->team1.players[mem->team1.b1id].status = "OUT";
                   break;
               }
           }
        }else{
            for(int i = mem->team1.b2id; i < 11; i++){
               if(mem->team1.players[i].status == "NOT PLAYED"){
                   mem->team1.b1id = i;
                   mem->team1.players[i].status = "NOT OUT";
                   mem->team1.players[mem->team1.b2id].status = "OUT";
                   break;
               }
           }
        }
    }else {
        if(mem->team2.players[mem->team2.b1id].on_strike){
            for(int i = mem->team2.b1id; i < 11; i++){
               if(mem->team2.players[i].status == "NOT PLAYED"){
                   mem->team2.b1id = i;
                   mem->team2.players[i].status = "NOT OUT";
                   mem->team2.players[mem->team2.b1id].status = "OUT";
                   break;
               }
            }
        }else{
            for(int i = mem->team2.b2id; i < 11; i++){
               if(mem->team2.players[i].status == "NOT PLAYED"){
                   mem->team2.b2id = i;
                   mem->team2.players[i].status = "NOT OUT";
                   mem->team2.players[mem->team2.b2id].status = "OUT";
                   break;
               }
            }
        }
    }
}

void write_to_files(){
    FILE *t1, *t2, *c;
    t1 = fopen("teamOut1.txt", "w");
    t2 = fopen("teamOut2.txt", "w");
    c = fopen("commentary.txt", "w");

    //team1
    fprintf(t1, "NAME		RUNS SCORED	BALLS PLAYED	STATUS		RUNS GIVEN	BALLS BOWLED	WICKETS TAKEN\n");
    int maxRuns = 0, maxBat = 0, maxWickets = 0, maxBowl = 0;
    for(int i = 0; i < 11; i++){
        struct Player p = mem->team1.players[i];
        if(p.runs > maxRuns){
            maxRuns = p.runs;
            maxBat = i;
        }
        if(p.wickets > maxWickets){
            maxWickets = p.wickets;
            maxBowl = i;
        }
        fprintf(t1, "%s\t\t%d\t\t%d\t\t%s\t\t%d\t\t%d\t\t%d\n", p.name, p.runs, p.balls_played, p.status, p.runs_given, p.balls_bowled, p.wickets);
    }
    
    //team2
    int maxRuns2 = 0, maxBat2 = 0, maxWickets2 = 0, maxBowl2 = 0;
    fprintf(t2, "NAME		RUNS SCORED	BALLS PLAYED	STATUS		RUNS GIVEN	BALLS BOWLED	WICKETS TAKEN\n");
    for(int i = 0; i < 11; i++){
        struct Player p = mem->team1.players[i];
        if(p.runs > maxRuns2){
            maxRuns2 = p.runs;
            maxBat2 = i;
        }
        if(p.wickets > maxWickets2){
            maxWickets2 = p.wickets;
            maxBowl2 = i;
        }
        fprintf(t2, "%s\t\t%d\t\t%d\t\t%s\t\t%d\t\t%d\t\t%d\n", p.name, p.runs, p.balls_played, p.status, p.runs_given, p.balls_bowled, p.wickets);
    }
    
    if(maxRuns > maxRuns2){
        fprintf(c, "Max runs scored by : %s (%d)\n", mem->team1.players[maxBat].name, maxRuns);
    }else{
        fprintf(c, "Max runs scored by : %s (%d)\n", mem->team2.players[maxBat2].name, maxRuns2);
    }

    if(maxWickets > maxWickets2){
        fprintf(c, "Max wickets taken by : %s (%d)\n", mem->team1.players[maxBowl].name, maxWickets);
    }else{
        fprintf(c, "Max wickets taken by : %s (%d)\n", mem->team2.players[maxBowl2].name, maxWickets2);
    }
}
#ifndef _CRICKET_HEADER_
#define _CRICKET_HEADER_

//structs
struct Player {
    int runs;
    int balls_played;
    char *status;
    int runs_given;
    int balls_bowled;
    int wickets; 
    int on_strike;
    char *name;
    int seed;
    int bowling;
};

struct Team {
    char *name;
    struct Player players[11];
    int seed;
    int batting;
    int b1pid;
    int b2pid;
    int bwpid;
    int b1id;
    int b2id;
    int bwid;
};

struct memory {
    struct Team team1;
    struct Team team2;
    int max_overs;
    int ump_seed;
    int overs;
    int balls;
    int ump_pid;
    int curr_res;
    int target;
};

struct memory * mem;

//functions

//memory
extern void init_ump();
extern void init_team1();
extern void init_team2();

//umpire
extern int toss();
extern int shot_hit();
extern void send_out();
extern void add_to_striker(int res);
extern void innings_over();
extern void over_change();
extern void write_to_files();

#endif
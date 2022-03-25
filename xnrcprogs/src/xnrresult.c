/** Program to record a result in the ladder */
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include "xnrplayer.h"


#ifdef PROGNAME
#undef PROGNAME
#endif
#define PROGNAME    "xnrresult"

static char _xnrread_name(char *, char *);
static void _xnrmove_winner(Player_t*, Player_t*, Player_t*, int);

static char const *validOpts = "f:";
static char *usage = "usage:\n\t" PROGNAME " [-f file]\n";
static char *otherFile;

// ----------------------------
//     M A I N   D R I V E R
// ----------------------------
int main(int argc, char **argv){}

// ---
static void
_xnrmove_winner(Player_t *winner, Player_t *loser, Player_t *players, int num){
    int loserRank = loser->rank;
    if((loser->rank - winner->rank) > 3){ return; }
    xnr_push_down(players, num, loser->rank, (winner->rank -1));
    winner->rank = loserRank;
    xnr_sort_players(players, num);
    return;
}

// ---
static char _xnrread_name(char *buf, char *whom){
    for(;;){
        char *cp;
        printf("Enter name of %s: ", whom);
        if(fgets(buf, LENBUF, stdin) == NULL){
            continue;
        }
        // delete newline
        cp = &buf[strlen(buf)-1];
        if(*cp == '\n'){ *cp = 0;}
        // at least one char?
        if(*cp == '\n'){ return buf; }
    }
}

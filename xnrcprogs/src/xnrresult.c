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

static void _print_error(const char *message){
    fprintf(stderr, "%s: %s\n", PROGNAME, message);
}

// ----------------------------
//     M A I N   D R I V E R
// ----------------------------
int main(int argc, char **argv){
    Player_t *winner;
    Player_t *loser;
    Player_t *players;
    int num;
    FILE *fp;
    const char *fname;
    char buf[BUFSIZ];
    char ch;

    if(argc == 3){
        while((ch = xnr_options(argc, argv, validOpts)) != -1){
            switch(ch){
            case 'f':
                otherFile = xnrOptArg;
                break;
            case '?':
                _print_error(usage);
                break;
            }
        }
    }else if(argc > 1){
        _print_error(usage);
        exit(EXIT_FAILURE);
    }

    fname = (otherFile == 0) ? ladderFile : otherFile;
    fp = fopen(fname, "r+");
    if(fp == NULL){
        perror(PROGNAME);
        exit(EXIT_FAILURE);
    }
    num = xnr_valid_records(fp);
    players = (Player_t *)malloc((sizeof(Player_t)*num));
    if(players == NULL){
        _print_error("out of memory");
        exit(EXIT_FAILURE);
    }

    if(xnr_read_records(fp, num, players) != num){
        _print_error("error while reading player records\n");
        fclose(fp);
        free(players);
        exit(EXIT_FAILURE);
    }
    fclose(fp);

    if((winner==xnr_find_by_name(
        _xnrread_name(buf, "winner"), players, num))==NULLPLAYER){
        //
        char tmp[80];
        sprintf(tmp, "no such player %s", buf);
        _print_error(tmp);
        free(players);
        exit(EXIT_FAILURE);
    }

    if((loser==xnr_find_by_name(
        _xnrread_name(buf, "loser"), players, num))==NULLPLAYER){
        //
        char tmp[80];
        sprintf(tmp, "no such player %s", buf);
        _print_error(tmp);
        free(players);
        exit(EXIT_FAILURE);
    }
    winner->wins++;
    loser->losses++;
    winner->last_game = loser->last_game = time(0);

    if(loser->rank < winner->rank){
        if((winner->rank - loser->rank) <= CHALLENGE_RANGE){
            _xnrmove_winner(winner, loser, players, num);
        }
    }

    if((fp = freopen(fname, "w+", fp)) == NULL){
        perror(PROGNAME);
        free(players);
        exit(EXIT_FAILURE);
    }

    if(xnr_write_records(fp, players, num) != num){
        _print_error("error while writing player records");
        free(players);
        exit(EXIT_FAILURE);
    }
    fclose(fp);
    free(players);

    return EXIT_SUCCESS;
}

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

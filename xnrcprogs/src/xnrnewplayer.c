/** Program to add a new player to the ladder.
 * The user is expected to assign a realistic ranking value to the player. */
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include "xnrplayer.h"

static const char *validOpts = "n:r:f:";
static char *otherFile;

#ifdef PROGNAME
#undef PROGNAME
#endif
#define PROGNAME    "xnrnewplayer"
static const char *usage = "usage:\n\t" PROGNAME " -r rank - name [-f file]\n"; 

/** record a player */
static void xnr_record(Player_t *player);

static void _print_error(const char *message){
    fprintf(stderr, "%s: %s\n", PROGNAME, message);
}

// ---------------------------
//    M A I N   D R I V E R
// ---------------------------
int main(int argc, char **argv){
    char ch;
    Player_t dummy;
    Player_t *new = &dummy;

    if(argc < 5){
        _print_error(usage);
        exit(EXIT_FAILURE);
    }

    while((ch = xnr_options(argc, argv, validOpts)) != -1){
        switch(ch){
        case 'f':
            otherFile = xnrOptArg;
            break;
        case 'n':
            strncpy(new->name, xnrOptArg, NAMELEN);
            new->name[NAMELEN] = 0;
            if(strcmp(new->name, xnrOptArg) != 0){
                fprintf(stderr, "Warning: name truncated to %s\n", new->name);
            }
            break;
        case 'r':
            if((new->rank = atoi(xnrOptArg)) == 0){
                _print_error(usage);
                exit(EXIT_FAILURE);
            }
            break;
        case '?':
            _print_error(usage);
            break;
        }
    }

    if((new->rank == 0)){
        _print_error("bad value for rank");
        exit(EXIT_FAILURE);
    }
    if(strlen(new->name) == 0){
        _print_error("needs a valid name for new player");
        exit(EXIT_FAILURE);
    }
    new->wins = new->losses = 0;
    time(&new->last_game); /* make now the time of the "last game" */ 
    xnr_record(new);

    return EXIT_SUCCESS;
}

// ---
static void xnr_record(Player_t *player){
    int num;
    int new_num;
    int i;
    Player_t *playerslist;
    const char *fname = (otherFile == 0) ? ladderFile : otherFile;
    FILE *fp;

    fp = fopen(fname, "r+");
    if(fp == NULL){
        if((fp = fopen(fname, "w")) == NULL){
            perror(PROGNAME);
            exit(EXIT_FAILURE);
        }
    }

    num = xnr_valid_records(fp);
    new_num = num + 1;
    if((player->rank <= 0) || (player->rank > new_num)){
        char buf[80];
        sprintf(buf, "rank must be between 1 and %d\n", new_num);
        _print_error(buf);
        exit(EXIT_FAILURE);
    }

    playerslist = (Player_t*)malloc(sizeof(Player_t)*new_num);

    if(playerslist == NULL){
        _print_error("out of memory");
        exit(EXIT_FAILURE);
    }

    if(xnr_read_records(fp, num, playerslist) != num){
        _print_error("error while reading player records");
        free(playerslist);
        exit(EXIT_FAILURE);
    }

    if(xnr_find_by_name(player->name, playerslist, num) != NULLPLAYER){
        char buf[80];
        sprintf(buf, "%s is already on the ladder", player->name);
        _print_error(buf);
        free(playerslist);
        exit(EXIT_FAILURE);
    }

    xnr_copy_player(&playerslist[num], player);
    if(player->rank != new_num){
        xnr_push_down(playerslist, num, player->rank, num);
    }

    xnr_sort_players(playerslist, new_num);
    if((fp = freopen(fname, "w+", fp)) == NULL){
        perror(PROGNAME);
        free(playerslist);
        exit(EXIT_FAILURE);
    }

    if(xnr_write_records(fp, playerslist, new_num) != new_num){
        _print_error("error while writing player records");
        fclose(fp);
        free(playerslist);
        exit(EXIT_FAILURE);
    }

    fclose(fp);
    free(playerslist);
}

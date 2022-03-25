#ifndef _XNRPLAYER_H
#define _XNRPLAYER_H
/** Definitions for functions prototype which manipulate player records */

#include<time.h>
#include "xnroptions.h"

#define NAMELEN             12      // max. for player name length
#define LENBUF              256     // max. for input buffer length
/** number of higher ranked players who may be challenged to move up in rank */
#define CHALLENGE_RANGE     3 

char *xnrOptArg;

typedef struct Player {
    char name[NAMELEN+1];
    int rank;
    int wins;
    int losses;
    time_t last_game;
} Player_t;

#define NULLPLAYER (Player_t *)0

extern const char *ladderFile;
extern const char *wrFmt;       /* used when writing records */
extern const char *rdFmt;       /* used when reading records */

/** Function prototypes */
int xnr_valid_records(FILE *);
int xnr_read_records(FILE *, int, Player_t *);
int xnr_write_records(FILE *, Player_t *, int);
Player_t *xnr_find_by_name(char *, Player_t *, int);
Player_t *xnr_find_by_rank(int, Player_t *, int);
void xnr_push_down(Player_t *, int, int, int);
int xnr_print_records(Player_t *, int);
void xnr_copy_player(Player_t *, Player_t*);
int xnr_compare_name(Player_t *, Player_t*);
int xnr_compare_rank(Player_t *, Player_t*);
void xnr_sort_players(Player_t *, int);

#endif

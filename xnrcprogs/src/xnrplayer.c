#include "xnrplayer.h"

const char *ladderFile = "ladder";
const char *wrFmt = " %12s  %d  %d  %d  %ld\n";
const char *rdFmt = " %12s  %d  %d  %d  %ld\n";

const char *headerLine = 
    "Player  Rank  Won  Lost  Last Game\n"
    "==================================\n";

const char *prtFmt = "%-12s%4d %4d %4d %4d %s\n";

/** Return the number of records in the data file */
int xnr_valid_records(FILE *fp){
    int i = 0;
    long players = 0L;
    long tmp = ftell(fp);
    char buf[LENBUF];

    fseek(fp, 0L, SEEK_SET);

    for(i=0; fgets(buf, LENBUF, fp) != NULL; i++){}

    // Restore the file pointer to original state
    fseek(fp, tmp, SEEK_SET);

    return i;

}

/** Read 'num' player records from 'fp' into the array 'them' */
int xnr_read_records(FILE *fp, int num, Player_t *players){
    int i = 0;
    
    if(num == 0){ return; }

    long tmp = ftell(fp);
    fseek(fp, 0L, SEEK_SET);

    for(i=0; i < num; i++){
        if(fscanf(
            fp, rdFmt, (players[i]).name, &((players[i]).rank),
            &((players[i]).wins), &((players[i]).losses),
            &((players[i]).last_game)) != 5
        ){
            break; // error of fscanf !
        }
    }
    fseek(fp, tmp, SEEK_SET);
    return i;
}

/** Write 'num' player records to the file 'fp' from the array 'them' */
int xnr_write_records(FILE *fp, Player_t *players, int num){
    int i = 0;
    fseek(fp, 0L, SEEK_SET);
    for(i=0; i < num; i++){
        if(fprintf(
            fp, wrFmt, (players[i]).name, (players[i]).rank,
            (players[i]).wins, (players[i]).losses,
            (players[i]).last_game) < 0){ break;}
    }

    return i;
}



/** Return a pointer to the player in array 'players' whose name
 *  matches 'name' */
Player_t *xnr_find_by_name(char *name, Player_t *players, int num){
    Player_t *player = players;
    int i = 0;
    for(i=0; i < num; i++, player++){
        if(strcmp(name, player->name) == 0){
            return player;
        }
    }

    return NULLPLAYER;
}


/** Return a pointer to the player in array 'them' whose rank matches 'rank' */

Player_t *xnr_find_by_rank(int rank, Player_t *players, int num){
    Player_t *player = players;
    int i = 0;

    for(i=0; i < num; i++, player++){
        if(rank == player->rank){
            return player;
        }
    }

    return NULLPLAYER;
}


/** Reduce by one the the ranking of all players in array 'players'
 * whose ranks are now between 'start' and 'end' */
void xnr_push_down(Player_t *players, int num, int start, int end){
    int i;
    Player_t *player;
    for(i=end; i >= start; i--){
        if((player = xnr_find_by_rank(i, players, num)) == NULLPLAYER){
            fprintf(stderr, "error: could not find player ranked %d\n", i);
            free(players);
            exit(EXIT_FAILURE);
        }else{ (player->rank)++; }
    }
}


/** Pretty print num player records from the array 'players' */
int xnr_print_records(Player_t *players, int num){
    int i = 0;
    printf("%s", headerLine);
    char tmpbuf[LENBUF];
    for(i=0; i < num; i++){
        int ret = sprintf(
            tmpbuf, prtFmt, (players[i]).name, (players[i]).rank,
            (players[i]).wins, (players[i]).losses,
            asctime(localtime(&(players[i]).last_game))
        );
        if(printf("%s", tmpbuf) < 0){ 
            break; //* error on printf!
        }
    }

    return i;
}


/** Copy the values from player 'from' to player 'to' */
void xnr_copy_player(Player_t *to, Player_t *from){
    if((to == NULLPLAYER) || (from == NULLPLAYER)){ return; }
    *to = *from;
    return;
}


/** Compare the names of two players */
int xnr_compare_name(Player_t *player1, Player_t *player2){
    return strcmp(player1->name, player2->name);
}

/** Compare the ranks of two players */
int xnr_compare_rank(Player_t *player1, Player_t *player2){
    return (player1->rank - player2->rank);
}


/** Sort num player records in the array 'players' by rank */
void xnr_sort_players(Player_t *players, int num){
    qsort(players, num, sizeof(Player_t), xnr_compare_rank);
}

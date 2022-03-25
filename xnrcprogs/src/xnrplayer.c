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
int xnr_read_records(FILE *fp, int num, Player_t *them){
    int i = 0;
    
    if(num == 0){ return; }

    long tmp = ftell(fp);
    fseek(fp, 0L, SEEK_SET);

    for(i=0; i < num; i++){
        if(fscanf(fp, rdFmt, (them[i]).name,
            &((them[i]).rank),
            &((them[i]).wins),
            &((them[i]).losses),
            &((them[i]).last_game)) != 5){ break; // error of fscanf !}
    }
    fseek(fp, tmp, SEEK_SET);
    return i;
}

/** Write 'num' player records to the file 'fp' from the array 'them' */
int xnr_write_records(FILE *fp, Player_t *them, int num){
    int i = 0;
    fseek(fp, 0L, SEEK_SET);
    for(i=0; i < num; i++){
        if(fprintf(
            fp, wrFmt, (them[i]).name, (them[i]).rank,
            (them[i]).wins, (them[i]).losses,
            (them[i]).last_game) < 0){ break; /* error on fprintf */}
    }

    return i;
}

//Player_t *xnr_find_by_name(char *, Player_t *, int);
//Player_t *xnr_find_by_rank(int, Player_t *, int);
//void xnr_push_down(Player_t *, int, int, int);
//int xnr_print_records(Player_t *, int);
//void xnr_copy_player(Player_t *, Player_t*);
//int xnr_compare_name(Player_t *, Player_t*);
//int xnr_compare_rank(Player_t *, Player_t*);
//void xnr_sort_players(Player_t *, int);

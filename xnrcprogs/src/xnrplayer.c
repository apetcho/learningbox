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

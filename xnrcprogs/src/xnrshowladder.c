/** Program to print the current ladder status */
#include "xnrplayer.h"

static const *validOpts = "f:";
static const *usage = "usage:\n\txnrshowladder [-f ladder_file]\n";
static char *otherFile;

static const char *progname = "xnrshowladder";

// -----------------------------
//    M A I N   D R I V E R 
// -----------------------------
int main(int argc, char **argv){
    int num;
    char ch;
    Player_t *players;
    const char *fname;
    FILE *fp;

    if(argc == 3){
        while((ch=xnr_options(argc, argv, validOpts)) != -1){
            switch(ch){
            case 'f':
                otherFile = xnrOptArg;
                break;
            case '?':
                fprintf(stderr, "%s", usage);
                break;
            }
        }
    }else if (argc > 1){
        fprintf(stderr, "%s", usage);
        exit(EXIT_FAILURE);
    }

    fname = (otherFile == 0) ? ladderFile : otherFile;
    fp = fopen(fname, "r+");
    if(fp == NULL){
        perror(progname);
        exit(EXIT_FAILURE);
    }

    num = xnr_valid_records(fp);
    players = (Player_t*)malloc((sizeof(Player_t)*num));

    if(players == NULL){
        fprintf(stderr, "%s: out of memory\n", progname);
        exit(EXIT_FAILURE);
    }

    if(xnr_read_records(fp, num, players) != num){
        fprintf(stderr, "%s: error while reading player records\n", progname);
        free(players);
        fclose(fp);
        exit(EXIT_FAILURE);
    }
    fclose(fp);
    xnr_sort_players(players, num);

    if(xnr_print_records(players, num) != num){
        fprintf(stderr, "%s: error while printing player records\n", progname);
        free(players);
        exit(EXIT_FAILURE);
    }

    free(players);

    return EXIT_SUCCESS;
}

#include<curses.h>
#include<stdlib.h>


void write_pages(){
    chtype acs_symbol[] = {
        ACS_ULCORNER,   ACS_LLCORNER,   ACS_URCORNER,
        ACS_LRCORNER,   ACS_LTEE,       ACS_RTEE,
        ACS_BTEE,       ACS_TTEE,       ACS_HLINE,
        ACS_VLINE,      ACS_PLUS,       ACS_S1,
        ACS_S9,         ACS_DIAMOND,    ACS_CKBOARD,
        ACS_DEGREE,     ACS_PLMINUS,    ACS_BULLET,
        ACS_LARROW,     ACS_RARROW,     ACS_DARROW,
        ACS_UARROW,     ACS_BOARD,      ACS_LANTERN,
        ACS_BLOCK,      ACS_S3,         ACS_S7,
        ACS_LEQUAL,     ACS_GEQUAL,     ACS_PI,
        ACS_NEQUAL,     ACS_STERLING
    };

    char acs_name[][20] = {
        "ACS_ULCORNER",   "ACS_LLCORNER",   "ACS_URCORNER",
        "ACS_LRCORNER",   "ACS_LTEE",       "ACS_RTEE",
        "ACS_BTEE",       "ACS_TTEE",       "ACS_HLINE",
        "ACS_VLINE",      "ACS_PLUS",       "ACS_S1",
        "ACS_S9",         "ACS_DIAMOND",    "ACS_CKBOARD",
        "ACS_DEGREE",     "ACS_PLMINUS",    "ACS_BULLET",
        "ACS_LARROW",     "ACS_RARROW",     "ACS_DARROW",
        "ACS_UARROW",     "ACS_BOARD",      "ACS_LANTERN",
        "ACS_BLOCK",      "ACS_S3",         "ACS_S7",
        "ACS_LEQUAL",     "ACS_GEQUAL",     "ACS_PI",
        "ACS_NEQUAL",     "ACS_STERLING"
    };

    int rows = 5;
    int page = 0;
    int i, j;
    int flag = 0;
    int acs_nr = sizeof(acs_symbol)/sizeof(chtype);

    for(j=0; j <= acs_nr/rows; j++){
        clear();
        for(i=0; i < rows; i++){
            if(page * rows + i <= acs_nr-1){
                mvaddch(i*2+1, 3, acs_symbol[page*rows+i]);
                mvaddstr(i*2+1, 8, acs_name[page*rows+i]);
            }else{
                flag = 1;
            }
        }

        if(!flag){
            mvaddstr(rows*2+2, 1, "Press Left Arrow (->) to move to next page");
        }else{
            mvaddstr(rows*2+2, 1, "Press Left Arrow (->) to quit");
        }
        refresh();
        page++;
        getch();
    }
}

void quit(){
    endwin();
}

// ---
int main(){
    initscr();
    atexit(quit);
    noecho();
    curs_set(0);

    write_pages();
    
    return EXIT_SUCCESS;
}

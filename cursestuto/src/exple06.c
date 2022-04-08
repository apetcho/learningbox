#include<curses.h>
#include<stdlib.h>

void quit(){ endwin(); }


// ----
int main(){
    initscr();
    atexit(quit);
    start_color();
    clear();

    init_pair(1, COLOR_GREEN, COLOR_RED);
    bkgd(COLOR_PAIR(1));

    mvaddstr(5, 5, "Hello");
    mvaddstr(6, 10, "World!");
    mvaddstr(24, 1, "Press any key to quit this application ");
    refresh();
    getch();

    return EXIT_SUCCESS;
}

#include<curses.h>
#include<stdlib.h>

void quit(){ endwin(); }

// ----
int main(){
    initscr();
    atexit(quit);
    start_color();
    clear();

    init_pair(1, COLOR_YELLOW, COLOR_BLUE);
    init_pair(2, COLOR_GREEN, COLOR_BLUE);
    bkgd(COLOR_PAIR(1));

    attrset(A_UNDERLINE);
    mvaddstr(5, 5, "Hello");
    attrset(A_BOLD);
    mvaddstr(6, 10, "World!");
    attrset(A_DIM | COLOR_PAIR(2));
    int x, y;
    getmaxyx(stdscr, y, x);
    mvaddstr(y-1, 1, "Press any key to quit this application");
    refresh();
    getch();

    return EXIT_SUCCESS;
}

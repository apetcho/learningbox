#include<curses.h>
#include<stdlib.h>

void quit(){ endwin(); }

// ----
int main(){
    initscr();
    atexit(quit);
    clear();
    noecho();
    curs_set(0);
    cbreak();
    keypad(stdscr, TRUE);

    mvaddstr(5, 5, "Hello");
    mvaddstr(6, 10, "World!");
    mvaddstr(24, 1, "Press any F1 to quit this application ");
    refresh();
    getch();
    while(getch() != KEY_F(1)){}

    return EXIT_SUCCESS;
}

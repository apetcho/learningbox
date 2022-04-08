#include<curses.h>
#include<stdlib.h>

void quit(){ endwin(); }

int main(){
    initscr();
    atexit(quit);
    mvaddstr(3, 2, "The difference between addch() and insch():");
    mvaddstr(5, 5, "addch(): HELLO, WORLD!");
    mvaddch(5, 15, 'X');

    mvaddstr(6, 5, "insch(): HELLO, WORLD!");
    mvinsch(6, 15, 'X');
    refresh();
    getch();

    return EXIT_SUCCESS;
}

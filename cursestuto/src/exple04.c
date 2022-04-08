#include<curses.h>
#include<stdlib.h>

void quit(){ endwin(); }

// ---
int main(){
    initscr();
    atexit(quit);
    start_color();
    clear();

    mvaddstr(5, 5, "Hello");
    mvaddstr(6, 10, "World!");
    mvaddstr(15, 1, "Press any KEY to quit");
    refresh();
    getch();
    
    return EXIT_SUCCESS;
}

#include<curses.h>
#include<stdlib.h>

void quit(){ endwin();}

// ---
int main(){
    initscr();
    atexit(quit);
    start_color();
    clear();

    init_pair(1, COLOR_GREEN, COLOR_RED);
    color_set(1, 0);

    mvaddstr(5, 5, "Hello");
    mvaddstr(6, 10, "World!");
    mvaddstr(15, 1, "Press any key to QUIT this application");
    refresh();
    getch();

    return EXIT_SUCCESS;
}

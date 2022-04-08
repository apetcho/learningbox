#include<curses.h>
#include<stdlib.h>

WINDOW *win1;
WINDOW *win2;

void quit(){
    delwin(win1);
    delwin(win2);
    endwin();
}


// ----
int main(){
    initscr();
    atexit(quit);
    clear();
    noecho();
    curs_set(0);
    cbreak();
    keypad(stdscr, 1);

    start_color();
    init_pair(1, COLOR_YELLOW, COLOR_BLUE);
    win1 = newwin(5, 20, 10, 10);
    win2 = subwin(stdscr, 5, 20, 10, 35);

    bkgd(COLOR_PAIR(1));

    mvaddstr(5, 5, "Hello stdscr");
    mvwaddstr(win1, 3, 3, "Hello newwin");
    mvwaddstr(win2, 3, 3, "Hello subwin");
    refresh();
    wrefresh(win1);
    wrefresh(win2);
    while(getch() != KEY_F(1)){}

    return EXIT_SUCCESS;
}

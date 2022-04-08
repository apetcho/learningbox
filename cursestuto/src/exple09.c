#include<curses.h>
#include<stdlib.h>

WINDOW *win;

void quit(){
    delwin(win);
    endwin();
}


// ---
int main(){
    initscr();
    atexit(quit);
    clear();
    curs_set(0);
    cbreak();
    keypad(stdscr, 1);
    start_color();
    init_pair(1, COLOR_YELLOW, COLOR_BLUE);
    init_pair(2, COLOR_BLUE, COLOR_WHITE);

    win = newwin(10, 30, 10, 30);
    bkgd(COLOR_PAIR(1));
    wbkgd(win, COLOR_PAIR(2));

    mvaddstr(5, 5, "Hello stdscr");
    mvaddstr(24, 1, "Press F1 to quit");
    mvwaddstr(win, 2, 3, "Hello win");
    mvwaddstr(win, 4, 3, "This a new subwindow!");
    refresh();
    wrefresh(win);

    while(getch() != KEY_F(1)){}

    return EXIT_SUCCESS;
}

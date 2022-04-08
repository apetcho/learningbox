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
    noecho();
    curs_set(0);
    cbreak();
    keypad(stdscr, 1);

    start_color();
    init_pair(1, COLOR_YELLOW, COLOR_BLUE);
    init_pair(2, COLOR_BLUE, COLOR_WHITE);

    win = newwin(5, 20, 10, 10);
    bkgd(COLOR_PAIR(1));
    wbkgd(win, COLOR_PAIR(2));

    mvaddstr(5, 5, "Hello stdscr");
    mvaddstr(23, 50, "Press F1 to quit");
    mvwaddstr(win, 3, 3, "Hello win");
    mvwaddstr(win, 7, 3, "This text is not visible");

    box(win, 0, 0);
    mvhline(7, 1, ACS_BULLET, 20);
    refresh();
    wrefresh(win);

    while(getch() != KEY_F(1)){}

    return EXIT_SUCCESS;
}

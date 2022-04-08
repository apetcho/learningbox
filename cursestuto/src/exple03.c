#include<curses.h>
#include<stdlib.h>

void quit(){ endwin(); }

int main(){
    int const i = 23456;
    double const f = -12345e-3;

    initscr();
    atexit(quit);
    curs_set(0);
    mvprintw(3, 2, "Integer number in Octal and Hexadecimal: %o | %x\n", i, i);
    mvprintw(4, 2, "Integer with padded with 0: %010d\n", i);
    mvprintw(5, 2, "Floating point number: %8.3f\n", f);
    mvprintw(6, 2, "Floating point number: %8.3f\n", f);
    mvprintw(7, 2, "Floating point number in Hexadecimal: %a\n", f);
    refresh();
    getch();

    return EXIT_SUCCESS;
}

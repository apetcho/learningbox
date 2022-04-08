#include<stdlib.h>
#include<menu.h>

ITEM **items;
MENU *menu;

void quit(){
    unpost_menu(menu);
    free_menu(menu);
    for(int i=0; i <= 4; i++){
        free_item(items[i]);
    }
    free(items);
    endwin();
}


// ----
int main(){
    int ch;
    initscr();
    atexit(quit);
    clear();
    noecho();
    curs_set(0);
    cbreak();
    nl();
    keypad(stdscr, TRUE);

    items = (ITEM**)calloc(5, sizeof(ITEM*));
    items[0] = new_item("M1", "");
    items[1] = new_item("M2", "");
    items[2] = new_item("M3", "");
    items[3] = new_item("END", "");
    items[4] = 0;

    menu = new_menu(items);
    post_menu(menu);

    mvaddstr(23, 3, "Press middle menu of F1 to quit");
    refresh();

    while((ch=getch()) != KEY_F(1)){
        switch(ch){
        case KEY_DOWN:
            menu_driver(menu, REQ_DOWN_ITEM);
            break;
        case KEY_UP:
            menu_driver(menu, REQ_UP_ITEM);
            break;
        case 0xA:
            if(item_index(current_item(menu)) == 3){
                exit(EXIT_SUCCESS);
            }
        }
    }

    return EXIT_SUCCESS;
}

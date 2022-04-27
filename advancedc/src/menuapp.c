/** justify.c: This program justifies text files */
#include<stddef.h>
#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include<wchar.h>
#include<wctype.h>
#include<locale.h>
#include<ctype.h>

#define BOLD            "\x1b[1m"
#define NORMAL          "\x1b[0m"
#define RED             "\x1b[31m"
#define BLACK           "\x1b[30m"
#define GREEN           "\x1b[32m"
#define CLEAR_SCREEN    "\x1b[2J"
#define CLEAR_EOL       "\x1b[K"
#define MOVE_CURSOR(x, y) do{                   \
        char buf[80];                           \
        sprintf(buf, "\x1b[%d;%df", (x), (y));  \
        size_t len = strlen(buf);               \
        char text[len+1];                       \
        strncpy(text, buf, len);                \
        text[len] = '\0';                       \
        printf("%s", text);                     \
    }while(0)


char header[] = 
    CLEAR_SCREEN
    BOLD"F"NORMAL"iles  "
    BOLD"E"NORMAL"dit   "
    BOLD"V"NORMAL"iew    "
    BOLD"P"NORMAL"roject "
    BOLD"R"NORMAL"un     "
    BOLD"D"NORMAL"ebug   "
    CLEAR_EOL
;

/* Line-drawing characters for the PC = " │ ┤ ⏋⎿ ⏊ ⏉ ├ ⎯ ┼ ┤" */

void menubar();
void do_new_file();
void do_open_file();
void do_close_file();
void do_save_file();
void do_saveas_file();
void do_print_file();
void do_exit_file();

char *szFiles[] = { 
    "-------------------",
    "| "BOLD"N"NORMAL"ew             |",
    "| "BOLD"O"NORMAL"pen            |",
    "| "BOLD"C"NORMAL"lose           |",
    "| "BOLD"S"NORMAL"ave            |",
    "| save "BOLD"A"NORMAL"s         |",
    "|-----------------|",
    "| "BOLD"P"NORMAL"rint           |",
    "| e"BOLD"X"NORMAL"it            |",
    "-------------------",
    NULL
};

void (*FilesFunctions[])(void) = {
    menubar,
    do_new_file,
    do_open_file,
    do_close_file,
    do_save_file,
    do_saveas_file,
    menubar,
    do_print_file,
    menubar,
    do_exit_file,
    menubar,
    NULL
};

void pull_down(char *menu[], int ncols, void (*callbacks[])(void));

// ------------------------
//  M A I N   D R I V E R 
// ------------------------
int main(int argc, char **argv){
    char choice;
    while(1){
        puts(header);
        choice = (char)getchar();
        if(choice == '\0' || choice == '\xE0'){
            choice = (char)getchar();
        }
        MOVE_CURSOR(10, 10);
        switch(toupper(choice)){
        case 'F':
            pull_down(szFiles, 1, FilesFunctions);
            break;
        case 'E':
            printf("%s" CLEAR_EOL, "Edit submenu called");
            break;
        case 'V':
            printf("%s" CLEAR_EOL, "View submenu called");
            break;
        case 'P':
            printf("%s" CLEAR_EOL, "Project submenu called");
            break;
        case 'R':
            printf("%s" CLEAR_EOL, "Run submenu called");
            break;
        case 'D':
            printf("%s" CLEAR_EOL, "Debug submenu called");
            break;
        default:
            printf("Invalid key!");
            puts(CLEAR_EOL);
            break;
        }
        break;
    }

    puts("");
    return EXIT_SUCCESS;
}


//
void pull_down(char *menu[], int ncols, void (*callbacks[])(void)){
    int menuItem = -1;
    char choice;
    for(int i=0; menu[i]; i++){
        MOVE_CURSOR(i+1, ncols);
        printf("%s\n", menu[i]);
    }

    while(menuItem < 0){
        choice = (char)getchar();
        if(choice == '\0' || choice == '\xE0'){
            choice = (char)getchar();
        }
        choice = toupper(choice);
        /* Find the correct menu item index */
        if(isalnum(choice)){
            for(int i=0; menu[i]; i++){
                if(strchr(menu[i], choice)){
                    menuItem = i;
                    break;
                }
            }
        }

        if(menuItem >= 0){
            callbacks[menuItem]();
        }
    }
}

//
void menubar(){
}

//
void do_new_file(){
    MOVE_CURSOR(20, 10);
    puts("Files, new");
    MOVE_CURSOR(21, 10);
    puts("Any key to continue");
    char c;
    scanf("%c", &c);
}

void do_open_file(){}
void do_close_file(){}
void do_save_file(){}
void do_saveas_file(){}
void do_print_file(){}
void do_exit_file(){}

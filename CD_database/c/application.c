#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<curses.h>

#define MAX_STRING      80      // Longest allowed response
#define MAX_ENTRY       1024    // Longest allowed database entry


#define MESSAGE_LINE    6       // Misc. message on this line
#define ERROR_LINE      22      // Line to use for errors
#define Q_LINE          20      // Line for questions
#define PROMPT_LINE     18      // Line for prompting on


/**
 * Define the needed global variables.
 */
static char current_cd[MAX_STRING] = '\0';
static char current_cat[MAX_STRING];

/**
 * Declare some filenames.
 * For simplicity, the files are fixed in this version
 */
const char *title_file = "title.cdb";
const char *tracks_file = "tracks.cdb";
const char *temp_file = "cdb.tmp";


/**
 * The function prototypes.
 */

void clear_all_screen(void);
void get_return(void);
int get_confirm(void);
int get_choice(char *greet, char *choices[]);
void draw_menu(char *options[], int highlight, int start_row, int start_col);
void insert_title(char *cdtitle);
void get_string(char *string);
void add_record(void);
void count_cds(void);
void find_cd(void);
void list_tracks(void);
void remove_tracks(void);
void remove_cd(void);
void update_cd(void);


/**
 * Menu tables
 */

// TODO: write each as: "[a] add new CD", ...
char *main_menu[] = {
    "add new CD",
    "find CD",
    "count CDs and tracks in the catalog",
    "quit",
    0,
};

char *extended_menu[] = {
    "add new CD",
    "find CD",
    "count CDs and tracks in the catalog",
    "list tracks on current CD",
    "remove current CD",
    "update track information",
    "quit",
    0,
};


/**/
int main()
{
    int choice;
    initscr();

    // main loop
    do {
        choice = get_choice("Options:",
                current_cd[0] ? extended_menu : main_menu);
        switch(choice){
        case 'q':
            break;
        case 'a':
            add_record();
            break;
        case 'c':
            count_cds();
            break;
        case 'f':
            find_cd();
            break;
        case 'l':
            list_tracks();
            break;
        case 'r':
            remove_cd();
            break;
        case 'u':
            update_cd();
            break;
        }
    }while(choice != 'q');
    endwin();

    return EXIT_SUCCESS;  // or exit(EXIT_SUCCESS);
}

/******************************
 * Functions' implementation  *
 ******************************/

// 1- Building the menu
/**
 * @brief Get the choice object
 * 
 * Prompt the user a menu to choose an option from.
 * 
 * @param greet   Introduction to the client/user 
 * @param choices Pointers array pointing the appropriate menu table.
 * @return int  Returns a character corresponding to the choice selected from the menu.
 */
int get_choice(char *greet, char *choices[]){
    static int selected_row = 0;
    int max_row = 0;
    int start_screenrow = MESSAGE_LINE;
    int start_screencol = 10;
    char **option;
    int selected;
    int key = 0;

    option = choices;
    // count the number of options available in this menu table.
    while(*option){
        max_row++;
        option++;
    }
    /* protect against menu getting shorter when CD deleted */
    if(selected_row >= max_row){
        selected_row = 0;
    }

    clear_all_screen();
    mvprintw(start_screenrow-2, start_screencol, greet);
    keypad(stdscr, TRUE);
    cbreak();
    noecho();
    key = 0;
    while(key != 'q' && key != KEY_ENTER && key != '\n'){
        if(key == KEY_UP){
            if(selected_row == 0)
                selected_row = max_row -1;
            else
            selected_row--;
        }
        if(key == KEY_DOWN){
            if(selected_row == (max_row - 1))
                selected_row = 0;
            else
            selected_row++;
        }
        selected = *choices[selected_row];
        draw_menu(choices, selected_row, start_screenrow, start_screencol);
        key = getch();
    }

    keypad(stdscr, FALSE);
    nocbreak();
    echo();

    if(key == 'q')
        selected = 'q';

    return selected;
}
void clear_all_screen(void);
void get_return(void);
int get_confirm(void);

void draw_menu(char *options[], int highlight, int start_row, int start_col);
void insert_title(char *cdtitle);
void get_string(char *string);
void add_record(void);
void count_cds(void);
void find_cd(void);
void list_tracks(void);
void remove_tracks(void);
void remove_cd(void);
void update_cd(void);



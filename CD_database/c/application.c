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



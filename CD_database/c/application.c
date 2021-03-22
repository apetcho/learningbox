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

/* Constants used in boxed subwindow*/
#define BOXED_LINES     11
#define BOXED_ROWS      60
#define BOX_LINE_POS    8
#define BOX_ROW_POS     2

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

// 2.
/**
 * @brief Draw Application Menu.
 * 
 * @param options       Options table
 * @param highlight     Highlighting flag
 * @param start_row     Starting row for text display on the screen
 * @param start_col     Starting column for text display on the screen
 */
void draw_menu(char *options[], int highlight, int start_row, int start_col){
    int current_row = 0;
    char **option_ptr;
    char *txt_ptr;
    option_ptr = options;

    while(*option_ptr){
        if(current_row == highlight)
            attron(A_STANDOUT);
        txt_ptr = options[current_row];
        txt_ptr++;
        mvprintw(start_row + current_row, start_col, "%s", txt_ptr);
        if(current_row == highlight)
            attroff(A_STANDOUT);
        current_row++;
        option_ptr++;
    }

    mvprintw(start_row + current_row + 3, start_col,
        "Move highligh then press Return " );
    refresh();
}

// 3.

/**
 * @brief Clear the screen.
 * 
 */
void clear_all_screen(void){
    clear();
    mvprintw(2, 20, "%s", "CD Datababse Application");
    if (current_cd[0]){
        mvprintw(ERROR_LINE, 0, "Current CD: %s %s\n",
            current_cat, current_cd);
    }

    refresh();
}

// Database File Manipulation
// --------------------------
/**
 * @brief Add a new CD record to the database.
 */
void add_record(void){
    char catalog_number[MAX_STRING];
    char cd_title[MAX_STRING];
    char cd_type[MAX_STRING];
    char cd_artist[MAX_STRING];
    char cd_entry[MAX_STRING];

    int screenrow = MESSAGE_LINE;
    int screencol = 10;

    clear_all_screen();
    mvprintw(screenrow, screencol, "Enter new CD details");
    screenrow += 2;

    mvprintw(screenrow, screencol, "Catalog Number: ");
    get_string(catalog_number);
    screenrow++;

    mvprintw(screenrow, screencol, "    CD Title: ");
    get_string(cd_title);
    screenrow++;

    mvprintw(screenrow, screencol, "    CD Type: ");
    get_string(cd_type);
    screenrow++;

    mvprintw(screenrow, screencol, "    Artist: ");
    get_string(cd_artist);
    screenrow++;

    mvprintw(PROMPT_LINE-2, 5, "About to add this new entry:");
    sprintf(cd_entry, "%s,%s,%s,%s", catalog_number,
        cd_title, cd_type, cd_artist);
    mvprintw(PROMPT_LINE, 5, "%s", cd_entry);
    refresh();
    mov(PROMPT_LINE, 0);
    if(get_confirm()){
        insert_title(cd_entry);
        strcpy(current_cd, cd_title);
        strcpy(current_cat, catalog_number);
    }
}

/**
 * @brief Prompts for and reads in a string at the current screen position.
 * 
 * It also deletes any trailing newline.
 * 
 * @param[out] string String read as client input. 
 */
void get_string(char *string){
    int len;
    wgetnstr(stdscr, string, MAX_STRING);
    len = strlen(string);
    if(len > 0 && string[len - 1] == '\n'){
        string[len-1] = '\0';
    }
}

/**
 * @brief Prompts and reads user confirmation.
 * 
 * It reads user's input string and checks the first character for Y or y.
 * If it finds any other character, it gives no confirmation.
 * 
 * @return Returns 1 if found 'y' or 'Y' otherwise returns 0.
 */
int get_confirm(void){
    int confirmed = 0;
    char first_char;

    mvprintw(Q_LINE, 5, "Are you sure? ");
    clrtoeol();
    refresh();

    cbreak();
    first_char = getch();
    if(first_char == 'Y' || first_char == 'y'){
        confirmed = 1;
    }
    nocbreak();

    if(!confirmed){
        mvprintw(Q_LINE, 1, "   Cancelled");
        clrtoeol();
        refresh();
        sleep(1);
    }

    return confirmed;
}

/**
 * @brief Adds a title to the CD database by appending the title string to the end
 * of the titles file.
 * 
 * @param cdtitle 
 */
void insert_title(char *cdtitle){
    FILE *fp = fopen(title_file, "a");
    if(!fp){
        mvprintw(ERROR_LINE, 0, "cannot open CD titles database");
    }else{
        fprintf(fp, "%s\n", cdtitle);
        fclose(fp);
    }
}

// -----------------
// Updating Records
// -----------------
void get_return(void);

void count_cds(void);
void find_cd(void);
void list_tracks(void);
void remove_tracks(void);
void remove_cd(void);
void update_cd(void);



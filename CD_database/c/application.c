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

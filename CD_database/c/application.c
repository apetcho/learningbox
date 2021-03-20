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

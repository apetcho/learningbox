/** numword.c: Program to count words in sentences. */
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#define TRUE    1
#define FALSE   0
#define BIGEST_LINE     256     // The biggest line readable from keyboard

int number_of_words(const char *text);

char input[BIGEST_LINE];

int main(){
    puts("Enter lines, when last one is entered");
    puts("provide a END-OF-FILE (Ctrl-Z on most systems)");
    puts("to end the program.\n");
    while(fgets(input, BIGEST_LINE, stdin)){
        size_t len = strlen(input);
        input[len-1] = '\0';
        printf("Words = %2d '%.50s'\n", number_of_words(input), input);
    }
    putchar('\n');

    return EXIT_SUCCESS;
}

/** number_of_words() */
int number_of_words(const char *text){
    int blank = TRUE;
    int count = 0;
    for(int i=0; text[i]; i++){
        if(text[i] != ' '){
            if(blank){ ++count;}
            blank = FALSE;
        }else{ blank = TRUE; }
    }

    return count;
}

#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<stdio.h>
#include "processfile.h"

/**
 * @brief Read a line of character strings from a file.
 * 
 * @param line 
 * @param len 
 * @param fp 
 * @return int 
 */
int read_line(char *line, size_t len, FILE *fp){
    memset(line, 0, len);
    char buf[len+1];
    memset(buf, 0, len);
    if(fp){
        fgets(buf, len, fp);
    }
    size_t xlen = strlen(buf);
    buf[xlen-1] = '\0';
    int i = 0;
    while(buf[i] != '\0'){
        *(line+i) = buf[i];
        ++i;
    }
    *(line+i) = '\0';

    return (int)strlen(line);
}

/**
 * @brief Parse a line of character string to extract person object field.
 * 
 * @param line 
 * @param delim 
 * @return Person_t 
 */
Person_t* parse_line(const char *line, const char *delim){
    enum {FNAME=0, LNAME, EMAIL};
    Person_t *person = person_alloc();
    char *token;
    char *text = strdup(line);
    int i = 0;
    while((token = strsep(&text, delim)) != NULL){
        if(i == FNAME){
            strncpy(person->fname, token, sizeof(person->fname));
        }else if(i == LNAME){
            strncpy(person->lname, token, sizeof(person->lname));
        }else if(i == EMAIL){
            strncpy(person->email, token, sizeof(person->email));
        }
        ++i;
    }

    return person;
}

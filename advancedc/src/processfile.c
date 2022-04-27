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
    char buf[len];
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
    //printf("%s\n", line);

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
        if(strcmp(token, "") == 0){ continue; }
        if(i == FNAME){
            strncpy(person->fname, token, PERSONLEN);
        }else if(i == LNAME){
            strncpy(person->lname, token, PERSONLEN);
        }else if(i == EMAIL){
            strncpy(person->email, token, PERSONLEN);
        }
        ++i;
    }

    return person;
}

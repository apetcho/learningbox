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

Person_t parse_line(const char *line, const char *delim){}

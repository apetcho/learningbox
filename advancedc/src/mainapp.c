#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#include "person.h"
#include "processfile.h"

#define FILENAME "../persondata.txt"

int main(){
    char buf[PERSONBUFLEN];
    int len = 0;
    Person_t *person;
    FILE *fp;
    fp = fopen(FILENAME, "r");
    if(fp == NULL){ exit(EXIT_FAILURE);}
    //int first = 0;
    while(!feof(fp)){
        len = read_line(buf, PERSONBUFLEN, fp);
        // if(first == 0){
        //     first = 1;
        //     continue;
        // }
        //printf("[%03d] %s\n", len, buf);
        person = parse_line(buf, ",");
        person_print(*person);
        printf("\n");
    }

    fclose(fp);
    return EXIT_SUCCESS;
}

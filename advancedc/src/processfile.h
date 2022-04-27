#ifndef __PROCESS_FILE_H_
#define __PROCESS_FILE_H_
#include<stddef.h>
#include<stdio.h>

#define PERSONLEN       30
#define MAXPERSON       1024
#define PERSONBUFLEN    94

typedef struct{
    char *fname;
    char *lname;
    char *email;
} Person_t;

Person_t* person_alloc();
void person_free(Person_t*);
void person_print(Person_t);

int read_line(char *line, size_t len);
Person_t parse_line(const char *line);
void read_file(char *buf[], size_t nitem, FILE *fp);


#endif

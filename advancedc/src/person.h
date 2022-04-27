#ifndef __PERSON_H_
#define __PERSON_H_
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

#endif

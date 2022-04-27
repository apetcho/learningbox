#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#include "person.h"
#include "processfile.h"
#include "linkedList.h"

#define MYBUFLEN    128

#define FILENAME "../persondata.txt"

/* private prototypes */
// alloc
Node* allocate(size_t size){
    Node *node = calloc(1, sizeof(Node));
    if(node == NULL){ return NULL; }
    node->data = (void*)person_alloc();
    if(node->data == NULL){ return NULL; }
    (void)size;
    node->next = NULL;

    return node;
}

// dealloc
static void deallocate(void *data){
    Person_t *person = (Person_t*)data;
    person_free(person);
    data = NULL;
}

// display
static void display(const void *data){
    Person_t *person = (Person_t*)data;
    person_print(*person);
}

// copy
static void copydata(void *dst, const void *src){
    Person_t *person;
    person = person_alloc();
    if(person == NULL){
        dst = NULL;
        return;
    }
    const Person_t *obj = (const Person_t*)src;
    strncpy(person->fname, obj->fname, PERSONLEN);
    strncpy(person->lname, obj->lname, PERSONLEN);
    strncpy(person->email, obj->email, PERSONLEN);
    dst = (void*)person;
}

// compare
static int compare(const void *a, const void *b){
    const Person_t *x = (const Person_t*)a;
    const Person_t *y = (const Person_t*)b;

    if(strcmp(x->fname, y->fname) < 0){ return -1;}
    if((strcmp(x->fname, y->fname) == 0) && (strcmp(x->lname, y->lname) < 0)){
        return -1;
    }
    if((strcmp(y->fname, y->fname)==0) && (strcmp(x->lname, y->lname)==0)){
        return 0;
    }
    return 1;
}

// to_string
static char personbuf[MYBUFLEN+1];
static const char* to_string(const void *data){
    const Person_t *person = (const Person_t*)data;
    memset(personbuf, '\0', sizeof(personbuf));
    snprintf(
        personbuf, MYBUFLEN,
        "Person(fname=%s, lname=%s, email=%s)",
        person->fname, person->lname, person->email
    );

    return personbuf;
}

// ------------------------------
//      M A I N   D R I V E R 
// ------------------------------
int main(int argc, char **argv){
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

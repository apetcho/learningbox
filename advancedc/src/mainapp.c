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
static void deallocate(Node *node){
    
}
// display
// copy
// compare
// to_string

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

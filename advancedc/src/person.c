#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include "person.h"

static void person_error(void *data, const char *routine){
    if(data == NULL){
        fprintf(
            stderr, "%s:: %s : %d [%s]\n",
            routine, __FILE__, __LINE__, strerror(errno)
        );
        exit(EXIT_FAILURE);
    }
    return;
}

/**
 * @brief Allocate memory to Person object
 * 
 * @return Person_t* 
 */
Person_t* person_alloc(){
    Person_t *person = (Person_t*)malloc(sizeof(Person_t));
    person_error(person, "person_alloc()");
    person->fname = (char*)malloc(sizeof(char)*PERSONLEN);
    person_error(person->fname, "person_alloc()");
    person->lname = (char*)malloc(sizeof(char)*PERSONLEN);
    person_error(person->lname, "person_alloc()");
    person->email = (char*)malloc(sizeof(char)*PERSONLEN);
    person_error(person->email, "person_alloc()");

    return person;
}

/**
 * @brief Release memory allocated to person object.
 * 
 * @param person 
 */
void person_free(Person_t* person){
    if(person){
        if(person->fname){ free(person->fname);}
        person->fname = NULL;
        if(person->lname){ free(person->lname);}
        person->lname = NULL;
        if(person->email){ free(person->email);}
        person->email = NULL;
        free(person);
    }
}

void person_print(Person_t person){}

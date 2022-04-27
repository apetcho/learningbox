#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include<errno.h>

#include "linkedList.h"

/**
 * @brief Create a new list
 * 
 * @param alloc   Node memory allocation routine
 * @param dealloc Node memory deallocation routine
 * @param disp    Node display routine
 * @param copy    Node copying routine
 * @return List*  Newly created routine or NULL if allocation failed
 */
List* list_create(
    allocateNodeFn alloc,
    deallocateNodeFn dealloc,
    printNodeFn disp,
    copyNodeFn copy
){
    List *list = malloc(sizeof(List));
    if(list == NULL){
        return NULL;
    }
    list->len = 0;
    list->alloc = alloc;
    list->free = dealloc;
    list->print = disp;
    list->copy = copy;
    return list;
}

/**
 * @brief Release all allocated memory owned by the list
 * 
 * @param list 
 */
void list_destroy(List* list){
    if(list == NULL){ return; }
    Node *cursor;
    Node *temp;
    cursor = list->head;
    while(cursor != NULL){
        temp = cursor;
        cursor = cursor->next;
        list->free(temp);
    }
    free(list);
    list = NULL;
}


void list_append(List *list, void *data){}
void list_prepend(List *list, void *data){}
void list_insert_after(List *list, void *data, Node *node){}
void list_insert_before(List *list, void *data, Node *node){}
void list_find(const List *list, void *data){}
void list_remove(List *list, void *data){}
void list_print(const List *list){}

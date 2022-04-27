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
    size_t size, allocateNodeFn alloc, deallocateNodeFn dealloc,
    printNodeFn disp, copyNodeFn copy, compareNodeFn cmp)
{
    List *list = malloc(sizeof(List));
    if(list == NULL){
        return NULL;
    }
    list->len = 0;
    list->itemsize = size;
    list->alloc = alloc;
    list->free = dealloc;
    list->print = disp;
    list->copy = copy;
    list->compare = cmp;
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

/**
 * @brief Append data to list
 * 
 * @param list 
 * @param data
 * @return List* 
 */
List* list_append(List *list, const void *data){
    Node *node = list->alloc(list->itemsize);
    list->copy(node->data, data);
    node->next = NULL;
    Node *cursor;
    cursor = list->head;
    while(cursor != NULL){
        cursor = cursor->next;
    }
    cursor = node;
    return list;
}

/**
 * @brief Prepend data to list
 * 
 * @param list 
 * @param data 
 * @return List* 
 */
List* list_prepend(List *list, const void *data){
    Node *node = list->alloc(list->itemsize);
    list->copy(node->data, data);
    node->next = list->head;
    list->head = node;

    return list;
}

/**
 * @brief Insert data after a given node in list
 * 
 * @param list 
 * @param data 
 * @param node 
 * @return List* 
 */
List* list_insert_after(List *list, const void *data, Node *node){
    Node *cursor;
    Node *target = NULL;
    cursor = list->head;
    Node *item = list->alloc(list->itemsize);
    list->copy(item->data, data);
    if(cursor == NULL){
        cursor = item;
        return list;
    }

    do{
        target = cursor;
        cursor = cursor->next;
        if(list->compare(target->data, node->data) == 0){ break;}
    }while(cursor != NULL || target != NULL);

    if(target == NULL || cursor == NULL){
        cursor = item;
        return list;
    }
    item->next = cursor;
    target->next = item;
    return list;
}


List* list_insert_before(List *list, const void *data, Node *node){}
Node* list_find(const List *list, const void *data){}
List* list_remove(List *list, const void *data){}
void list_print(const List *list){}

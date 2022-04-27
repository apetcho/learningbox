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
    list->len = 0;
    list->itemsize = 0;
}

/**
 * @brief Append data to list
 * 
 * If memory allocation of the input data failed, issue a warning and return
 * the unmodified list.
 * @param list 
 * @param data
 * @return List* 
 */
List* list_append(List *list, const void *data){
    if(data == NULL){ return list; }
    Node *node = list->alloc(list->itemsize);
    if(node == NULL){
        fprintf(stderr, "WARNING: %s\n", strerror(errno));
        return list;
    }
    list->copy(node->data, data);
    node->next = NULL;
    Node *cursor;
    cursor = list->head;
    while(cursor != NULL){
        cursor = cursor->next;
    }
    cursor = node;
    list->len++;
    return list;
}

/**
 * @brief Prepend data to list
 * 
 * If memory allocation of the input data failed, issue a warning and return
 * the unmodified list.
 * @param list 
 * @param data 
 * @return List* 
 */
List* list_prepend(List *list, const void *data){
    Node *node = list->alloc(list->itemsize);
    if(node == NULL){
        fprintf(stderr, "WARNING: %s\n", strerror(errno));
        return list;
    }
    list->copy(node->data, data);
    node->next = list->head;
    list->head = node;
    list->len++;

    return list;
}

/**
 * @brief Insert data after a given node in list
 * 
 * If the node is NULL, just return the original list unmodified.
 * If a memory allocation failed, issue a warning and return the the original
 * list unmodified.
 * If the node is not in list, just append data
 * 
 * @param list 
 * @param data 
 * @param node 
 * @return List* 
 */
List* list_insert_after(List *list, const void *data, Node *node){
    if(node == NULL){ return list; }
    Node *cursor;
    Node *target = NULL;
    Node *item = list->alloc(list->itemsize);
    if(item == NULL){
        fprintf(stderr, "WARNING: %s\n", strerror(errno));
        return list;
    }
    list->copy(item->data, data);
    cursor = list->head;
    if(cursor == NULL){ // The list is empty, just insert
        cursor = item;
        list->len++;
        return list;
    }

    do{
        target = cursor;
        cursor = cursor->next;
        if(list->compare(target->data, node->data) == 0){ break;}
    }while(cursor != NULL);

    if(cursor == NULL){ // The node is not in the list, just append
        cursor = item;
        list->len++;
        return list;
    }
    /* The node is found, insert the data at the proper position */
    item->next = cursor;
    target->next = item;
    list->len++;
    return list;
}

/**
 * @brief Insert data before a given node in the list
 * 
 * @param list 
 * @param data 
 * @param node 
 * @return List* 
 */
List* list_insert_before(List *list, const void *data, Node *node){
    if(node == NULL){ return list; }
    Node *prev;
    Node *cursor;
    Node *item;
    item = list->alloc(list->itemsize);
    list->copy(item->data, data);
    cursor = list->head;
    if(cursor == NULL){
        cursor = item;
        list->len++;
        return list;
    }
    prev = cursor;
    Node *tmp;
    while(cursor != NULL){
        tmp = cursor->next;
        if(list->compare(tmp->data, node->data) == 0){ break;}
        prev = cursor;
        cursor = tmp;
    }
    if(cursor == NULL){
        item->next = NULL;
        prev->next = item;
        list->len++;
        return list;
    }
    item->next = cursor;
    prev->next = item;
    list->len++;
    return list;
}


/**
 * @brief Search for data in list
 * 
 * Return a pointer to the node containing the data or NULL if not found.
 * @param list 
 * @param data 
 * @return Node* 
 */
Node* list_find(const List *list, const void *data){
    Node *cursor;
    cursor = list->head;
    while(cursor != NULL){
        if(list->compare(cursor->data, data) == 0){
            break;
        }
        cursor = cursor->next;
    }

    return cursor;
}


/**
 * @brief delete the first node containing data
 * 
 * @param list 
 * @param data 
 * @return List* 
 */
List* list_remove(List *list, const void *data){
    Node *cursor;
    Node *temp;
    cursor = list->head;
    while(cursor != NULL){
        if(list->compare(cursor->data, data) == 0){
            temp = cursor;
            cursor = cursor->next;
            list->free(temp);
            list->len -= 1;
            temp = NULL;
            break;
        }
        cursor = cursor->next;
    }
    return list;
}

/**
 * @brief Print data in list
 * 
 * @param list 
 */
void list_print(const List *list){
    if(list->len == 0){
        printf("[ ]");
        return;
    }
    Node *cursor;
    cursor = list->head;
    if(list->len == 1){
        printf("[ ");
        list->print(cursor->data);
        printf(" ]");
        return;
    }
    printf("[ ");
    while(cursor != NULL){
        list->print(cursor->data);
        if(cursor->next != NULL){printf(", ");}
        cursor = cursor->next;
    }
    printf(" ]");

}

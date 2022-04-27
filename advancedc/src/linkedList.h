#ifndef __LINKEDLIST_H_
#define __LINKEDLIST_H_
#include<stddef.h>

typedef struct Node{
    void *data;
    struct Node *next;
}Node;

typedef Node* (*allocateNodeFn)(size_t);
typedef void (*deallocateNodeFn)(void*);
typedef void (*printNodeFn)(const void*);
typedef void (*copyNodeFn)(void*, const void*);
typedef int (*compareNodeFn)(const void*, const void *);
typedef const char* (*toStringFn)(const void*);

typedef struct List{
    Node *head;
    int len;
    size_t itemsize;
    allocateNodeFn alloc;
    deallocateNodeFn free;
    printNodeFn print;
    copyNodeFn copy;
    compareNodeFn compare;
    toStringFn to_string;
} List;


// ----- List routines ----
List* list_create(
    size_t size,
    allocateNodeFn alloc,
    deallocateNodeFn dealloc,
    printNodeFn disp,
    copyNodeFn copy,
    compareNodeFn cmp,
    toStringFn toString
);

void list_destroy(List* list);
List* list_append(List *list, const void *data);
List* list_prepend(List *list, const void *data);
List* list_insert_after(List *list, const void *data, Node *node);
List* list_insert_before(List *list, const void *data, Node *node);
Node* list_find(const List *list, const void *data);
List* list_remove(List *list, const void *data);
void list_print(const List *list);
const char* list_toString(const List* list);

#endif

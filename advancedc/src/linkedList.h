#ifndef __LINKEDLIST_H_
#define __LINKEDLIST_H_
#include<stddef.h>

typedef struct Node{
    void *data;
    struct Node *next;
}Node;

typedef struct {
    Node *head;
    Node *alloc(size_t len);
    void free(Node *node);
    void print(Node node);
    void copy(Node *dst, const Node *src);
} List;

typedef Node* (*allocateNodeFn)(size_t);
typedef void (*deallocateNodeFn)(Node*);
typedef void (*printNodeFn)(Node);
typedef void (*copyNodeFn)(Node*, const Node*);

// ----- List routines ----
List* list_create(
    allocateNodeFn alloc,
    deallocateNodeFn dealloc,
    printNodeFn disp,
    copyNodeFn copy
);

void list_destroy(List* list);
void list_append(List *list, void *data);
void list_prepend(List *list, void *data);
void list_insert_after(List *list, void *data, Node *node);
void list_insert_before(List *list, void *data, Node *node);
void list_find(const List *list, void *data);
void list_remove(List *list, void *data);
void list_print(const List *list);

#endif

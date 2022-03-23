#ifndef _XNR_OBJECT_H
#define _XNR_OBJECT_H

#include<stdarg.h>
#include<stddef.h>

typedef struct xnr_class{
    size_t size;
    void* (*ctor)(void *self, va_list *args);
    void* (*dtor)(void *self);
    void (*draw)(const void *self);
} xnr_class;

void* xnr_new(const void* klass, ...);
void xnr_delete(void *item);
void xnr_draw(const void *self);

#endif

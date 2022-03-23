#ifndef _XNR_OBJECT_H
#define _XNR_OBJECT_H

#include<stdarg.h>
#include<stddef.h>
#include<stdio.h>

typedef struct xnr_object_ xnr_object_t;
typedef struct xnr_class_  xnr_class_t;

struct xnr_object_{
    const xnr_class_t *klass;   /* object description */
};

struct xnr_class_{
    const xnr_object_t _;                       /* class description */
    const char *name;                           /* class name */
    const xnr_class_t *super;                   /* super class */
    size_t size;                                /* object size */
    void* (*ctor)(void *self, va_list *args);
    void* (*dtor)(void *self);
    int (*differ)(const void *self, const void *b);
    int (*puto)(const void *self, FILE *fp);
};

void* xnr_super_ctor(const void *klass, void *self, va_list *argp);
void* xnr_super_dtor(const void *klass, void *self);
int xnr_super_differ(const void *klass, const void *self, const void *b);
int xnr_super_puto(const void *klass, const void *self, FILE *fp);

extern const void *xnr_object;
extern const void *xnr_class;

void* xnr_new(const void* klass, ...);
void xnr_delete(void *item);
const void* xnr_classof(const void *self);
size_t xnr_sizeof(const void *self);
void* xnr_ctor(void *self, va_list *argp);
void* xnr_dtor(void *self);
int xnr_differ(const void *self, const void *b);
int xnr_puto(const void *self, FILE *fp);
const void* xnr_super(const void *self);


#endif

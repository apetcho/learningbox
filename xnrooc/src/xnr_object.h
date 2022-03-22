#ifndef _XNR_OBJECT_H
#define _XNR_OBJECT_H

#include<stddef.h>

typedef struct xnr_class xnr_class;

void* xnr_new(const void* klass, ...);
void xnr_delete(void *item);
void* xnr_clone(const void *self);
int xnr_differ(const void *self, const void *other);
size_t xnr_sizeof(const void *self);
size_t xnr_len(const void *self);


#endif

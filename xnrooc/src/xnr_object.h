#ifndef _XNR_OBJECT_H
#define _XNR_OBJECT_H

extern const void* xnr_object;
void* xnr_new(const void* type, ...);
void xnr_delete(void* xnrobj);
int xnr_differ(const void *lhs, const void *rhs);

#endif

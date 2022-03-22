#ifndef _XNR_SET_H
#define _XNR_SET_H

extern const void* xnr_set;

void* xnr_set_add(void* set, const void* element);
void* xnr_set_find(const void* set, const void* element);
void* xnr_set_drop(void* set, const void* element);
int xnr_set_contains(void* set, const void* element);
unsigned xnr_set_length(void* set, const void* element);

#endif

#ifndef _XNR_VALUE_H
#define _XNR_VALUE_H

/** Node types */
extern const void *xnr_minus;
extern const void *xnr_value;
extern const void *xnr_mult;
extern const void *xnr_div;
extern const void *xnr_add;
extern const void *xnr_sub;

/** Tree management */
void* xnr_new(const void *type, ...);
void xnr_process(const void *tree);
void xnr_delete(void *tree);

#endif

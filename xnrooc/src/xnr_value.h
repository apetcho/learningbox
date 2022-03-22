#ifndef _XNR_VALUE_H
#define _XNR_VALUE_H

/** Node types */
const void *xnr_minus;
const void *xnr_value;
const void *xnr_mult;
const void *xnr_div;
const void *xnr_add;
const void *xnr_sub;

/** Tree management */
void* xnr_new(const void *type, ...);
void xnr_process(const void *tree);
void xnr_delete(void *tree);

#endif

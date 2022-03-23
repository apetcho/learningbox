#ifndef _XNR_VALUE_H
#define _XNR_VALUE_H

#include<stdarg.h>

typedef struct xnr_type_{
    void *(*new)(va_list arg);
    double (*exec)(const void *tree);
    void (*delete)(void *tree);
} xnr_type_t;

double xnr_exec(const void *tree);

typedef struct xnr_binary_op{
    const void *type;
    void *left;
    void *right;
} xnr_binary_op_t;

#define XNR_GETLEFT(tree) (((xnr_binary_op_t*)tree)->left)
#define XNR_GETRIGHT(tree) (((xnr_binary_op_t*)tree)->right)

void *xnr_make_binary_op(va_list args);
void xnr_free_binary_op(void *tree);


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

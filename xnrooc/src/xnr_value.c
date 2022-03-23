#include<stdlib.h>
#include<stdio.h>
#include<stdarg.h>
#include<assert.h>

#include "xnr_parser.h"
#include "xnr_value.h"


/***/
void* xnr_new(const void *type, ...){
    va_list args;
    void *result;
    assert(type && ((xnr_type_t*)type)->new);
    va_start(args, type);
    result = ((xnr_type_t*)type)->new(args);
    *(const xnr_type_t **)result = type;
    va_end(args);

    return result;
}

/***/
double xnr_exec(const void *tree){
    assert(tree && *(xnr_type_t **)tree && (*(xnr_type_t**)tree)->exec);
    return (*(xnr_type_t **)tree)->exec(tree);
}

/***/
void xnr_process(const void *tree){
    printf("\t%g\n", _xnr_exec(tree));
}


/***/
void xnr_delete(void *tree){
    assert(tree && *(xnr_type_t **)tree && (*(xnr_type_t**)tree)->delete);
    (*(xnr_type_t**)tree)->delete(tree);   
}

/** Number */
typedef struct xnr_value{
    const void *type;
    double value;
}xnr_value_t;

/***/
static void* _make_value(va_list args){
    xnr_value_t *node = malloc(sizeof(xnr_value_t));
    assert(node);
    node->value = va_arg(args, double);
    return node;
}

/***/
static double _do_value(const void *tree){
    return ((xnr_value_t*)tree)->value;
}

/** unary operators */
typedef struct xnr_unary_op{
    const void *type;
    void *arg;
} xnr_unary_op_t;

/***/
static void* _make_unary_op(va_list args){
    xnr_unary_op_t *node = malloc(sizeof(*node));
    assert(node);
    node->arg = va_arg(args, void*);
    return node;
}

/***/
static double _do_minus(const void *tree){
    return - _xnr_exec(((xnr_unary_op_t*)tree)->arg);
}


static void _free_unary_op(void *tree){
    xnr_delete(((xnr_unary_op_t*)tree)->arg);
    free(tree);
}

/** binary operator */
typedef struct xnr_binary_op{
    const void *type;
    void *left;
    void *right;
} xnr_binary_op_t;

static void* _make_binary_op(va_list args){
    xnr_binary_op_t *node = malloc(sizeof(*node));
    assert(node);
    node->left = va_arg(args, void *);
    node->right = va_arg(args, void *);
    return node;
}

/***/
static double _do_add(const void *tree){
    return (
        _xnr_exec(((xnr_binary_op_t*)tree)->left) +
        _xnr_exec(((xnr_binary_op_t*)tree)->right)
    );
}

/***/
static double _do_sub(const void *tree){
    return (
        _xnr_exec(((xnr_binary_op_t*)tree)->left) -
        _xnr_exec(((xnr_binary_op_t*)tree)->right)
    );
}

/***/
static double _do_mult(const void *tree){
    return (
        _xnr_exec(((xnr_binary_op_t*)tree)->left) *
        _xnr_exec(((xnr_binary_op_t*)tree)->right)
    );
}

/***/
static double _do_div(const void *tree){
    double left = _xnr_exec(((xnr_binary_op_t*)tree)->left);
    double right = _xnr_exec(((xnr_binary_op_t*)tree)->right);
    if(right == 0.0){
        xnr_error("division by zero");
    }
    return left / right;
}

/***/
static void _free_binary_op(void *tree){
    xnr_delete(((xnr_binary_op_t*)tree)->left);
    xnr_delete(((xnr_binary_op_t*)tree)->right);
    free(tree);
}

/** types */
static xnr_type_t _Add = {_make_binary_op, _do_add, _free_binary_op};
static xnr_type_t _Sub = {_make_binary_op, _do_sub, _free_binary_op};
static xnr_type_t _Mult = {_make_binary_op, _do_mult, _free_binary_op};
static xnr_type_t _Div = {_make_binary_op, _do_div, _free_binary_op};
static xnr_type_t _Minus = {_make_unary_op, _do_minus, _free_unary_op};
static xnr_type_t _Value= {_make_value, _do_value, free};

const void *xnr_add = &_Add;
const void *xnr_sub = &_Sub;
const void *xnr_div = &_Div;
const void *xnr_mult = &_Mult;
const void *xnr_minus = &_Minus;
const void *xnr_value = &_Value;

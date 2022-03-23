#include<stdlib.h>
#include<stdarg.h>
#include<stdio.h>
#include<assert.h>

#include "xnr_parser.h"
#include "xnr_value.h"

/** Postfix driver */
typedef struct xnr_type{
    const char *name;
    void* (*new)(va_list args);
    void (*exec)(const void *tree);
    void (*delete)(void *tree);
}xnr_type_t;

void* xnr_new(const void *type, ...){}
static void _xnr_exec(const void *tree){}
void xnr_process(const void *tree){}
void xnr_delete(void *tree){}

// Number
typedef struct xnr_value_{
    const void *type;
    double value;
} xnr_value_t;

static void* _make_value(va_list args){}
static void _do_value(const void *tree){}

// unary operators
typedef struct xnr_unary_op{
    const void *type;
    void *arg;
}xnr_unary_op_t;

static void* _make_unary_op(va_list args){}
static void _do_unary_op(const void *tree);
static void _free_unary_op(void *tree){}


// binary op
typedef struct xnr_binary_op{
    const void *type;
    const *left;
    const *right;
}xnr_binary_op_t;

static void* _make_binary_op(va_list args){}
static void _do_binary_op(const void *tree);
static void _free_binary_op(void *tree){}

// types
static xnr_type_t _Add = {"+", _make_binary_op, _do_binary_op, _free_binary_op};
static xnr_type_t _Sub = {"-", _make_binary_op, _do_binary_op, _free_binary_op};
static xnr_type_t _Mul = {"*", _make_binary_op, _do_binary_op, _free_binary_op};
static xnr_type_t _Div = {"/", _make_binary_op, _do_binary_op, _free_binary_op};
static xnr_type_t _Minus = {
    "minus", _make_unary_op, _do_unary_op, _free_unary_op
};
static xnr_type_t _Value = { "", _make_value, _do_value, free};

const void *xnr_add = &_Add;
const void *xnr_sub = &_Sub;
const void *xnr_mult = &_Mul;
const void *xnr_minus = &_Minus;
const void *xnr_value = &_Value;

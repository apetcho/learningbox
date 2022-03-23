#include<stdlib.h>
#include<string.h>
#include<assert.h>

#include "xnr_name.h"
#include "xnr_parser.h"
#include "xnr_variable.h"
#include "xnr_value.h"

/**/
typedef struct xnr_variable_{
    xnr_name_t _;
    double value;
} xnr_variable_t;

#define XNR_VALUE(tree) (((xnr_variable_t*)tree)->value)

static void* _xnr_make_variable(va_list arg){
    xnr_variable_t *node = calloc(1, sizeof(*node));
    const char *name = va_arg(arg, const char*);
    size_t len = strlen(name);
    
    assert(node);
    node->_.name = malloc(len+1);
    assert(node->_.name);
    strcpy((void*)node->_.name, name);
    node->_.token = XNRTOK_VAR;

    return node;
}

static double _do_varibale(const void *tree){
    return XNR_VALUE(tree);
}

static void _free_variable(void *tree){}

//
static double _do_assign(const void *tree){
    return XNR_VALUE(XNR_GETLEFT(tree)) = xnr_exec(XNR_GETRIGHT(tree));
}

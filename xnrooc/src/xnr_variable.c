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

/** Variable types */
static xnr_type_t _Var = {_xnr_make_variable, _do_varibale, _free_variable};
static xnr_type_t _Assign = {
    xnr_make_binary_op, _do_assign, xnr_free_binary_op};

const void* xnr_variable = &_Var;
const void* xnr_assign = &_Assign;

void xnr_init_const(void){
    static const xnr_variable_t constants[] = {
        {{&_Var, "PI", XNRTOK_CONST},  3.14159265358979323846},
		{{&_Var, "E", XNRTOK_CONST},   2.71828182845904523536},
		{{&_Var, "GAMMA", XNRTOK_CONST}, 0.57721566490153286060}, /*Euler */
		{{&_Var, "DEG", XNRTOK_CONST}, 57.29577951308232087680},  /*deg/radian*/
		{{ &_Var, "PHI", XNRTOK_CONST}, 1.61803398874989484820 },
		{{ 0 }}
    };

    const xnr_variable_t *vp;
    for(vp = constants; vp->_.name; ++vp){
        xnr_install(vp);
    }
}

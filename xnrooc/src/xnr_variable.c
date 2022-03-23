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
    
}

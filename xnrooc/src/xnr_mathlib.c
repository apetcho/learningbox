#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<errno.h>

#include "xnr_name.h"
#include "xnr_mathlib.h"
#include "xnr_value.h"
#include "xnr_parser.h"

typedef struct xnr_math_{
    xnr_name_t _;
    double (*fun)(double);
}xnr_math_t;

#define XNR_FUNCTION(tree) (((xnr_math_t*)XNR_GETLEFT(tree))->fun)

static double _do_math(const void *tree){
    double result = xnr_exec(XNR_GETRIGHT(tree));

    errno = 0;
    result = XNR_FUNCTION(tree)(result);
    if(errno){
        xnr_error(
            "error in %s: %s",
            ((xnr_math_t *)XNR_GETLEFT(tree))->_.name,
            strerror(errno)
        );
    }
    return result;
}

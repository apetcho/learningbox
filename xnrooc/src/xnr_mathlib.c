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

static void _free_math(void *tree){
    xnr_delete(XNR_GETRIGHT(tree));
    free(tree);
}

static xnr_type_t _Math = {xnr_make_binary_op, _do_math, _free_math};
const void *xnr_math = &_Math;

void xnr_init_math(void){
    static const xnr_math_t functions[] = {
        {{ &_Math, "sin",   XNRTOK_MATH },  sin },
		{{ &_Math, "cos",   XNRTOK_MATH },  cos },
		{{ &_Math, "tan",   XNRTOK_MATH },  tan },
		{{ &_Math, "asin",  XNRTOK_MATH },  asin },
		{{ &_Math, "acos",  XNRTOK_MATH },  acos },
		{{ &_Math, "atan",  XNRTOK_MATH },  atan },
		{{ &_Math, "sinh",  XNRTOK_MATH },  sinh },
		{{ &_Math, "cosh",  XNRTOK_MATH },  cosh },
		{{ &_Math, "tanh",  XNRTOK_MATH },  tanh },
		{{ &_Math, "exp",   XNRTOK_MATH },  exp },
		{{ &_Math, "log",   XNRTOK_MATH },  log },
		{{ &_Math, "log10", XNRTOK_MATH },  log10 },
		{{ &_Math, "sqrt",  XNRTOK_MATH },  sqrt },
		{{ &_Math, "ceil",  XNRTOK_MATH },  ceil },
		{{ &_Math, "floor", XNRTOK_MATH },  floor },
		{{ &_Math, "abs",   XNRTOK_MATH },  fabs },
        {{0}}
    };

    const xnr_math_t *mp;
    for(mp=functions; mp->_.name; ++mp){
        xnr_install(mp);
    }
}

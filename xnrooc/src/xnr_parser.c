#include<stdlib.h>
#include<stdarg.h>
#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<setjmp.h>
#include<errno.h>

#include "xnr_parser.h"
#include "xnr_value.h"

/** Scanner */
static xnr_token_t token;   // current input symbol
static double number;       // current numerical value

/** return toke = next input sysmbol */
static xnr_token_t _xnr_scan(const char *buf){
    static const char *bufPtr;
    if(buf){ bufPtr = buf; }
    while(isspace(*bufPtr & 0xff)){ ++bufPtr; }

    if(isdigit(*bufPtr & 0xff) || *bufPtr == '.'){
        errno = 0;
        token = XNR_NUMBER;
        number = strtod(bufPtr, (char**)&bufPtr);
        if(errno == ERANGE){
            xnr_error("bad value: %s", strerror(errno));
        }
    }else{
        token = *bufPtr ? *bufPtr++: 0;
    }
    return token;
}

// factor: + factor | - factor | XNR_NUMBER | (sum)

static void* _xnr_sum(void);

static void* _xnr_factor(void){}

// product : factor { * | / factor } ...
static void* _xnr_product(void){}

// sum : product { + | - product } ...
static void* _xnr_sum(void){}

//
static jmp_buf onError;

/** MAIN DRIVER */
int main(void){
    volatile int errors = 0;
    char buf[BUFSIZ];
    if(setjmp(onError)){ ++errors; }

    // mainloop
    while(fgets(buf, sizeof (buf), stdin)){
        if(_xnr_scan(buf)){
            void *tree = _xnr_sum();
            if(token){xnr_error("trash after sum");}
            xnr_process(tree);
            xnr_delete(tree);
        }
    }

    return errors > 0;
}

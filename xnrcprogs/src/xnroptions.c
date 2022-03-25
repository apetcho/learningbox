#include<stdio.h>
#include<string.h>

#include "xnroptions.h"

int xnrOptIndex = 1;        /* first options should be argv[1] */
char *xnrOptArg = NULL;     /* global option argument pointer */

static const char XNR_SWITCH_CHAR = '-';
static const char XNR_UNKNOWN = '?';

int xnr_options(int argc, char **argv, const char *legal){
    static char *posn = "";     /* position in argv[xnrOptIndex] */
    char *legal_index = NULL;
    int letter = 0;

    if(!*posn){
        /* no more args, no XNR_SWITCH_CHAR or no option letter ? */
        if((xnrOptIndex >= argc)||
            (*(posn = argv[xnrOptIndex]) != XNR_SWITCH_CHAR) ||
            !*++posn){
            return -1;
        }
        /* find double XNR_SWITCH_CHAR ? */
        if(*posn == XNR_SWITCH_CHAR){
            xnrOptIndex++;
            return -1;
        }
    }
    letter = *posn++;
    if(!(legal_index = strchr(legal, letter))){
        if(!*posn){ xnrOptIndex++; }
        return XNR_UNKNOWN;
    }
    if(*++legal_index != ':'){
        /* no option argument */
        xnrOptArg = NULL;
        if(!*posn){ xnrOptIndex++; }
    }else{
        if(*posn){
            /* no space between opt and opt arg */
            xnrOptArg = posn;
        }else{
            if(argc <= ++xnrOptIndex){
                posn = "";
                return XNR_UNKNOWN;
            }else{
                xnrOptArg = argv[xnrOptIndex];
                posn = "";
                xnrOptArg++;
            }
        }
    }
    return letter;
}

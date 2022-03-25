/**
 * @file xnrgrep.c
 * @author Eyram K. Apetcho (orion2dev@gmail.com)
 * @brief A simple program to match pattern in a text file.
 * @version 0.1
 * @date 2022-03-25
 * 
 * @copyright Copyright (c) 2022
 * 
 * Distributed under the terms of the Modified BSD License.
 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#include "xnroptions.h"

int xnrOptIndex;        /* current index into argv[] */
int xnrOptArg;          /* global option argument pointer */

// Declarations for the pattern program
#define CFLAG   0x001   /* only count the number of matching lines */
#define IFLAG   0x002   /* ignore case of letters */
#define LFLAG   0x004   /* show line numbers */
#define NFLAG   0x008   /* show input file names */
#define VFLAG   0x010   /* show lines which do NOT match */


/** Record the required options ready to control program behaviour */
unsigned xnr_set_flags(int, char **, const char *);

/** Check each line of the input file for a match */
int xnr_look_in(const char*, const char*, unsigned);

/** Print a line from the input file on the standard output in the format
*** specified by the command line switches */
void print_line(unsigned mask, const char *fname, int lnno, const char *text);


/** Legal options for pattern */
static const char *OptString = "cilnvu";
/** Message when options or arguments incorrect */
static const char *errmsg = "usage:\n\txnrgrep [-cilnv] word [filename]\n";


/*****************************/
/*   M A I N   D R I V E R   */
/*****************************/
int main(int argc, char **argv){
    unsigned flags = 0;
    int success = 0;
    char *search_string;

    if(argc < 2){
        fprintf(stderr, errmsg);
        exit(EXIT_FAILURE);
    }

    flags = xnr_set_flags(argc, argv, OptString);
    if(argv[xnrOptIndex]){
        search_string = argv[xnrOptIndex];
    }else{
        fprintf(stderr, errmsg);
        exit(EXIT_FAILURE);
    }

    if(flags & IFLAG){
        /** ignore case by dealing only with lowercase */
        char *p;
        for(p = search_string; *p; p++){
            if(isupper(*p)){
                *p = tolower(*p);
            }
        }
    }

    if(argv[xnrOptIndex] == NULL){
        /* no file name given, so use stdin */
        success = xnr_look_in(NULL, search_string, flags);
    }else{
        while(argv[xnrOptIndex] != NULL){
            success += xnr_look_in(argv[xnrOptIndex++], search_string, flags);
        }
    }

    if(flags & CFLAG){
        printf("%d\n", success);
    }

    return success ? EXIT_SUCCESS : EXIT_FAILURE;
}

// ---
unsigned xnr_set_flags(int argc, char **argv, const char *opts){
    unsigned flags = 0;
    int ch = 0;
    while((ch = xnr_options(argc, argv, opts)) != -1){
        switch(ch){
        case 'c':
            flags |= CFLAG;
            break;
        case 'i':
            flags |= IFLAG;
            break;
        case 'l':
            flags |= LFLAG;
            break;
        case 'n':
            flags |= NFLAG;
            break;
        case 'v':
            flags |= VFLAG;
            break;
        case '?':
        default:
            fprintf(stderr, errmsg);
            exit(EXIT_FAILURE);
        }
    }

    return flags;
}

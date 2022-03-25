#ifndef _XNROPTIONS_H
#define _XNROPTIONS_H

extern int xnrOptIndex;     /* current index into argv[] */
extern char *xnrOptArg;     /* global option argument pointer */

/**
 * @brief Parses options letters and options argumentes from argv list.
 * 
 * Successive calls return successive options letters which match one of
 * thos in the legal list. Options letters may require option arguments
 * as indicated by a ':' following the letter in the legal list. For example
 * a legal list of "ab:c" implies that a, b and c are all valid options and
 * that b takes an option arguments. The option argument ist passed back to
 * the calling function in the value of global xnrOptArgs pointer. The 
 * xnrOptIndex gives the next string int the argv[] array that has not already
 * been processed by xnr_options().
 * 
 * @param argc argument count
 * @param argv argument list
 * @param legal valid or legal option letters
 * @return int
 * Returns -1 if the are no more option letters or if double XNR_SWITCH_CHAR
 * is found. Double XNR_SWITCH_CHAR forces xnr_options to finish processing
 * options.
 * 
 * Returns '?' if an option not in the legal set is encountered or an option
 * needing an argument is found without an arguments following it.
 */
int xnr_options(int argc, char **argv, const char *legal);
#endif

#ifndef __PROCESS_FILE_H_
#define __PROCESS_FILE_H_
#include<stddef.h>
#include<stdio.h>

#include "person.h"

int read_line(char *line, size_t len);
Person_t parse_line(const char *line);
void read_file(char *buf[], size_t nitem, FILE *fp);


#endif

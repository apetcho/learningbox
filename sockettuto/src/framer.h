#ifndef _FRAMER_H
#define _FRAMER_H
#include<stdio.h>
#include<stdint.h>

int get_next_msg(FILE *in, uint8_t *buf, size_t bufSize);
int put_msg(uint8_t buf[], size_t msgSize, FILE *out);

#endif

#ifndef _VOTE_ENCODING_H
#define _VOTE_ENCODING_H
#include<stdbool.h>
#include<stdint.h>
#include<stddef.h>

#include "voteProtocol.h"

bool decode(uint8_t *inBuf, size_t mSize, VoteInfo *info);
size_t encode(VoteInfo *info, uint8_t *outBuf, size_t bufSize);

#endif

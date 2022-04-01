#ifndef _VOTE_ENCODING_H
#define _VOTE_ENCODING_H
#include<stdbool.h>
#include<stdint.h>
#include<stddef.h>

#include "voteProtocol.h"

bool decode(uint8_t *inBuf, const size_t mSize, VoteInfo *info);
size_t encode(const VoteInfo *info, uint8_t *outBuf, const size_t bufSize);

#endif

/**
 * Routines for Text encoding of vote messages.
 * 
 * Wire Format:
 *      "Voting <v|i> [R] <candidate ID> <count>"
 */
#include "common.h"
//#include "voteProtocol.h"
#include "voteEncoding.h"

#include<stdlib.h>
#include<string.h>


static const char *MAGIC = "Voting";
static const char *VOTESTR = "v";
static const char *INQSTR = "i";
static const char *RESPONSESTR = "R";
static const char *DELIMISTR = " ";

enum{ BASE = 10 };

/**
 * Encode voting message info as a text string.
 * WARNING: Message will be silently truncated if buffer is too small!
 * Invariants (e.g. 0 <= candidate <= 1000) not checked.
 */
size_t encode(const VoteInfo *info, uint8_t *outBuf, const size_t bufSize){
    uint8_t *bufPtr = outBuf;
    long size = (size_t)bufSize;
    int rv = snprintf((char*)bufPtr, size, "%s %c %s %d",
        MAGIC, (info->isInquiry ? 'i': 'v'),
        (info->isResponse ? "R": ""), info->candidate
    );
    bufPtr += rv;
    size -= rv;
    if(info->isResponse){
        rv = snprintf((char*)bufPtr, size, " %llu", info->count);
        bufPtr += rv;
    }

    return (size_t)(bufPtr - outBuf);
}

bool decode(uint8_t *inBuf, size_t mSize, VoteInfo *info){}

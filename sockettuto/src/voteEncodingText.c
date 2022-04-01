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

/**
 * Extract message information from given buffer.
 * Note: modifies input buffer.
 */
bool decode(uint8_t *inBuf, const size_t mSize, VoteInfo *info){
    char *token;
    token = strtok((char*)inBuf, DELIMISTR);
    // Check for magic
    if(token == NULL || strcmp(token, MAGIC) != 0){
        return false;
    }

    // Get vote/inquiry indicator
    token = strtok(NULL, DELIMISTR);
    if(token == NULL){ return false; }

    if(strcmp(token, VOTESTR) == 0){
        info->isInquiry = false;
    }else if(strcmp(token, INQSTR) == 0){
        info->isInquiry = true;
    }else{ return false; }

    // Next token is either Response flag or candidate ID
    token = strtok(NULL, DELIMISTR);
    if(token == NULL){ return false; /* Message too short */ }

    if(strcmp(token, RESPONSESTR) == 0){// Response flag present
        info->isResponse = true;
        token = strtok(NULL, DELIMISTR); // Get candidate ID
        if(token == NULL){ return false; }
    }else{ // No response flag; token is candidate ID
        info->isResponse = false;
    }
    // Get candidate #
    info->candidate = atoi(token);
    if(info->isResponse){ // Response message should contain a count value
        token = strtok(NULL, DELIMISTR);
        if(token == NULL){
            return false;
        }
        info->count = strtoll(token, NULL, BASE);
    }else{
        info->count = 0L;
    }
    return true;
}

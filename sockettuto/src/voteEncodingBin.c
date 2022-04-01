/**
 * Routines for binary encoding of vote messages
 * 
 * Wire Format:
 *                               1  1  1  1  1  1
 * 0  1  2  3  4  5  6  7  8  9  0  1  2  3  4  5
 * +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
 * |     Magic       |Flags|       ZERO            |
 * +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
 * |                Candidate ID                   |
 * +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
 * |                                               |
 * |            Vot Count (only in response)       |
 * |                                               |
 * +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
 */
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>

#include "common.h"
#include "voteProtocol.h"
#include "voteEncoding.h"

enum{
    REQUEST_SIZE = 4,
    RESPONSE_SIZE = 12,
    COUNT_SHIFT = 32,
    INQUIRE_FLAG = 0x0100,
    RESPONSE_FLAG = 0x0200,
    MAGIC = 0x5400,
    MAGIC_MASK = 0xfc00,
};

typedef struct VoteMsgBin{
    uint16_t header;
    uint16_t candidateID;
    uint32_t countHigh;
    uint32_t countLow;
} VoteMsgBin;

// ---
size_t encode(const VoteInfo *info, uint8_t *outBuf, const size_t bufSize){
    if((info->isResponse && bufSize < sizeof(VoteMsgBin))||bufSize < 2*sizeof(uint16_t)){
        //
        die_with_user_message("Output buffer too small", "");
    }

    VoteMsgBin *vm = (VoteMsgBin*)outBuf;
    memset(outBuf, 0, sizeof(VoteMsgBin)); // 
    vm->header = MAGIC;
    if(info->isInquiry){
        vm->header |= INQUIRE_FLAG;
    }
    if(info->isResponse){
        vm->header |= RESPONSE_FLAG;
    }
    vm->header = htons(vm->header); // Byte order
    vm->candidateID = htons(info->candidate);
    if(info->isResponse){
        vm->countHigh = htonl(info->count >> COUNT_SHIFT);
        vm->countLow = htonl((uint32_t)info->count);
        return RESPONSE_SIZE;
    }else{
        return REQUEST_SIZE;
    }
}


bool decode(uint8_t *inBuf, const size_t mSize, VoteInfo *info){}



#ifndef _VOTE_PROTOCOL_H
#define _VOTE_PROTOCOL_H
#include<stdint.h>
#include<stdbool.h>

typedef struct VoteInfo{
    uint64_t count;
    int candidate;
    bool isInquiry;
    bool isResponse;
}VoteInfo;

enum{
    MAX_CANDIDATE = 1000,
    MAX_WIRE_SIZE = 500
};

#endif

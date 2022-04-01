#include<stdlib.h>
#include<string.h>

#include "common.h"

/**
 *  Read 2-byte length and place in big-endian order.
 * 
 * Then read the indicated number of bytes.
 * If the input buffer is too small for for the data, truncate to fit and
 * return the negation of the *indicated* length. Thus a negative return
 * other than -1 indicates that the message was truncated.
 * 
 * (Ambiguty is possible only if the caller passes an empty buffer.)
 * Input stream is always left empty.
 */
int get_next_msg(FILE *in, uint8_t *buf, size_t bufSize){
    uint16_t mSize = 0;
    uint16_t extra = 0;
    if(fread(&mSize, sizeof(uint16_t), 1, in) != 1){ return -1; }
    mSize = ntohs(mSize);
    if(mSize > bufSize){
        extra = mSize - bufSize;
        mSize = bufSize;
    }
    if(fread(buf, sizeof(uint8_t), mSize, in) != mSize){
        fprintf(stderr, "Framing error: expected %d, read less\n", mSize);
        return -1;
    }

    if(extra > 0){ // Message was truncated
        uint8_t waste[BUFSIZ];
        fread(waste, sizeof(uint8_t), extra, in); // Try to flush the channel
        return -(mSize+extra); // Negation of indicated size
    }else{
        return mSize;
    }
}

int put_msg(uint8_t buf[], size_t msgSize, FILE *out){}

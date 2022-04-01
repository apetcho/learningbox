#include "common.h"
#include "framer.h"

#include<stdlib.h>

static const char DELIMITER = '\n';

/**
 * Read up to bufSize bytes or until delimiter, copying into the given buffer
 * as we go.
 * 
 * Encountering EOF after some data buf before delimiter result in failure.
 * (That is: EOF is not a valid delimiter.)
 * 
 * Returns the number of bytes placed in buf (Delimiter NOT transfferred).
 * If buffer fills without encountering delimiter, negative count is returned.
 * If stream ends before first byte, -1 is returned.
 * 
 * Precondition: buf has room for at least bufSize bytes.
 */

int get_next_msg(FILE *in, uint8_t *buf, size_t bufSize){
    int count = 0;
    char nextChar;
    while(count < bufSize){
        nextChar = getc(in);
        if(nextChar == EOF){
            if(count > 0){
                die_with_user_message("get_next_msg()",
                    "Stream ended prematurely");
            }else{
                return -1;
            }
        }
        if(nextChar == DELIMITER){
            break;
        }
        buf[count++] = nextChar;
    }
    if(nextChar != DELIMITER){ // Out of space: count == bufSize
        return -count;
    }else{ // Found delimiter
        return count;
    }
}

/**
 * Write the given message to the outut stream, followed by the delimiter.
 * Return number of bytes written, or -1 on failure.
 */
int put_msg(uint8_t buf[], size_t msgSize, FILE *out){
    // Check for delimiter in message
    for(int i=0; i < msgSize; i++){
        if(buf[i] == DELIMITER){
            return -1;
        }
    }
    if(fwrite(buf, 1, msgSize, out) != msgSize){
        return -1;
    }
    fputc(DELIMITER, out);
    fflush(out);
    return msgSize;
}

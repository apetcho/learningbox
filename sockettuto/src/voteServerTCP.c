#include "common.h"
#include "voteProtocol.h"
#include "voteEncoding.h"
#include "framer.h"

#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<unistd.h>

static uint64_t counts[MAX_CANDIDATE+1];


// ----------------------------
//     M A I N   D R I V E R
// ----------------------------
int main(int argc, char **argv){
    if(argc != 2){
        die_with_user_message("Parameter(s)", "<Server Port/Service>");
    }

    int servSock = setup_tcp_server_socket(argv[1]);
    // servSock is now ready to accept connections

    for(;;){
        // Wait for a client to connect
        int clntSock = accept_tcp_connection(servSock);

        // Create an input stream from the socket
        FILE *channel = fdopen(clntSock, "r+");
        if(channel == NULL){
            die_with_system_message("fdopen() failed");
        }

        // Receive messages until connection closes
        int mSize;
        uint8_t inBuf[MAX_WIRE_SIZE];
        VoteInfo info;
        while((mSize = get_next_msg(channel, inBuf, MAX_WIRE_SIZE)) > 0){
            memset(&info, 0, sizeof(info)); // Clear vot information
            printf("Received message (%d bytes)\n", mSize);
            if(decode(inBuf, mSize, &info)){
                if(!info.isResponse){ // Ignore non-requests
                    info.isResponse = true;
                    if(info.candidate >= 0 && info.candidate <= MAX_CANDIDATE){
                        if(!info.isInquiry){
                            counts[info.candidate] += 1;
                        }
                        info.count = counts[info.candidate];
                    }// Ignore invalid candidates
                }
                uint8_t outBuf[MAX_WIRE_SIZE];
                mSize = encode(&info, outBuf, MAX_CANDIDATE);
                if(put_msg(outBuf, mSize, channel) < 0){
                    fputs("Error framing/outputting message\n", stderr);
                    break;
                }else{
                    printf("Processed %s for candidate %d; current count "
                        "is %llu.\n",
                        (info.isInquiry ? "inquiry" : "vote"),
                        info.candidate, info.count
                    );
                }
                fflush(channel);
            }else{
                fputs("Parse error, closing connection.\n", stderr);
                break;
            }
        }
        puts("Client finished");
        fclose(channel);
    }// Each client

    // NOT REACHED

    return EXIT_SUCCESS;
}

#include "common.h"
#include "voteProtocol.h"
#include "voteEncoding.h"
#include "framer.h"

#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<errno.h>
#include<netinet/in.h>


// ---------------------------
//    M A I N   D R I V E R
// ---------------------------
int main(int argc, char **argv){
    if(argc < 4 || argc > 5){
        die_with_user_message("Parameter(s)",
            "<Server> <Port/Service> <Candidate> [I]");
    }

    char *server = argv[1];     // server address/name
    char *service = argv[2];    // server port/service
    int candidate = atoi(argv[3]);
    if(candidate < 0 || candidate > MAX_CANDIDATE){
        die_with_user_message("Canadidate # not valid", argv[3]);
    }

    bool inq = (argc > 4 && strcmp(argv[4], "I") == 0);

    // Create a conected TCP client
    int sock = setup_tcp_client_socket(server, service);
    if(sock < 0){
        die_with_user_message("setup_tcp_client_socket() failed",
            "unable to connect");
    }

    FILE *str = fdopen(sock, "r+");     // wrap for stream I/O
    if(str == NULL){
        die_with_system_message("fdopen() failed");
    }

    // Set up info for a request
    VoteInfo info;
    memset(&info, 0, sizeof(info));
    info.isInquiry = inq;
    info.candidate = candidate;

    // Encode for transmission
    uint8_t outbuf[MAX_WIRE_SIZE];
    size_t reqSize = encode(&info, outbuf, MAX_WIRE_SIZE);

    // Print info
    printf("Sending %d-byte %s for candidate %d...\n", reqSize,
        (inq ? "inquiry" : "vote"), candidate);

    // Frame and send
    if(put_msg(outbuf, reqSize, str) < 0){
        die_with_system_message("put_msg() failed");
    }

    // Receive and print response
    uint8_t inbuf[MAX_WIRE_SIZE];
    size_t respSize = get_next_msg(str, inbuf, MAX_WIRE_SIZE);
    if(decode(inbuf, respSize, &info)){ // Parse it
        printf("Received:\n");
        if(info.isResponse){ printf("    Response to ");}
        if(info.isInquiry){ printf("inquiry ");}
        else{printf("vote ");}
        printf("for candidate %d\n", info.candidate);
        if(info.isResponse){
            printf("    count = &llu\n", info.count);
        }
    }

    // Close up
    fclose(str);

    return EXIT_SUCCESS;
}

#include<stdlib.h>
#include<string.h>

#include "common.h"

static const int MAXPENDING = 5;    // Maximum outstanding connection requests

// ----
int main(int argc, char **argv){
    if(argc != 2){
        die_with_user_message("Parameter(s)", "<Server Port>");
    }

    in_port_t servPort = (in_port_t)atoi(argv[1]); // Local port

    /** Create socket for incoming connections */
    int servSock;   // Socket descriptor for server
    if((servSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0){
        die_with_system_message("socket() failed");
    }

    /** Construct local address structure */
    struct sockaddr_in servAddr;            // Local address
    memset(&servAddr, 0, sizeof(servAddr)); // Zero out structure
    servAddr.sin_family = AF_INET;          // IPv4 address family
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY); // Any incoming interface
    servAddr.sin_port = htons(servPort);    // Local port

    /** Bind to the local address */
    if(bind(servSock, (struct sockaddr *)&servAddr, sizeof(servAddr)) < 0){
        die_with_system_message("bind() failed");
    }

    /** Mark the socket so it will listen for incoming connections */
    if(listen(servSock, MAXPENDING)< 0){
        die_with_system_message("listen() failed");
    }

    /** Main loop */
    for(;;){ // Run forever
        struct sockaddr_in clntAddr;        // Client address
        /** Set length of client address structure (in-out parameter) */
        socklen_t clntAddrLen = sizeof(clntAddr);

        /** Wait for a client to connect */
        int clntSock = accept(
            servSock, (struct sockaddr*)&clntAddr, &clntAddrLen);

        if(clntSock < 0){
            die_with_system_message("accept() failed");
        }

        /** clntSock is connect to a client */
        char clntName[INET_ADDRSTRLEN]; // String to contain client address
        if(inet_ntop(AF_INET, &clntAddr.sin_addr.s_addr,
            clntName, sizeof(clntName)) != NULL){
            printf(
                "Handling client %s/%d\n", clntName, ntohs(clntAddr.sin_port)
            );
        }else{
            puts("Unable to get client address");
        }

        handle_tcp_client(clntSock);
    }

    // NOT REACHED
    return EXIT_SUCCESS;
}

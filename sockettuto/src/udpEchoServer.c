#include<stdlib.h>
#include<string.h>

#include "common.h"


// ------
int main(int argc, char **argv){
    if(argc != 2){
        die_with_user_message("Parameter(s)", "<Server Port/Service>");
    }

    char *service = argv[1];        // local port / service

    // Contruct the server address structure
    struct addrinfo addrCriteria;
    memset(&addrCriteria, 0, sizeof(addrCriteria));
    addrCriteria.ai_family = AF_UNSPEC;
    addrCriteria.ai_flags = AI_PASSIVE;
    addrCriteria.ai_socktype = SOCK_DGRAM;
    addrCriteria.ai_protocol = IPPROTO_UDP;

    struct addrinfo *servAddr;
    int retVal = getaddrinfo(NULL, service, &addrCriteria, &servAddr);
    if(retVal != 0){
        die_with_user_message("getaddrinfo() failed", gai_strerror(retVal));
    }

    // Create socket for incoming connections
    int sock = socket(servAddr->ai_family, servAddr->ai_socktype, 
        servAddr->ai_protocol);

    if(sock < 0){
        die_with_system_message("socket() failed");
    }

    // Bind to the local address
    if(bind(sock, servAddr->ai_addr, servAddr->ai_addrlen) < 0){
        die_with_system_message("bind() failed");
    }

    // Free address list allocated by getaddrinfo()
    freeaddrinfo(servAddr);

    for(;;){
        struct sockaddr_storage clntAddr;
        // Set Length of client address structure (in-out parameter)
        socklen_t clntAddrLen = sizeof(clntAddr);

        // Block until receive message from a client
        char buffer[MAXSTRINGLENGTH];   // I/O buffer
        // Size of received message
        ssize_t numBytesRcvd =recvfrom(sock, buffer, MAXSTRINGLENGTH, 0,
            (struct sockaddr *)&clntAddr, &clntAddrLen);

        if(numBytesRcvd < 0){
            die_with_system_message("recvfrom() failed");
        }
        fputs("Handling client", stdout);
        print_socket_address((struct sockaddr*)&clntAddr, stdout);
        fputc('\n', stdout);

        // Send received datagram back to the client
        ssize_t numBytesSent = sendto(sock, buffer, numBytesRcvd, 0,
            (struct sockaddr*)&clntAddr, sizeof(clntAddr));
        if(numBytesSent < 0){
            die_with_system_message("sendto() failed");
        }else if(numBytesSent != numBytesRcvd){
            die_with_user_message("sendto()", "sent unpected number of bytes");
        }
    }

    // NOT REACHED
    return EXIT_SUCCESS;
}

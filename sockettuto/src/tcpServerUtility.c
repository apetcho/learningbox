#include<string.h>
#include<stdlib.h>
#include<unistd.h>

#include "common.h"

// ----
static const int MAXPENDING = 5;    // Maximum outstanding connection requests

// ----
int accept_tcp_connection(int servSock){
    struct sockaddr_storage clntAddr;   // Client address
    /* Set length of client address structure (in-out parameter) */
    socklen_t clntAddrLen = sizeof(clntAddr);

    /* Wait for a client to connect */
    int clntSock = accept(servSock, (struct sockaddr*)&clntAddr, &clntAddrLen);
    if(clntSock < 0){
        die_with_system_message("accept() failed");
    }

    /* clntSock is connected to a client! */
    fputs("Handling client ", stdout);
    print_socket_address((struct sockadd*)&clntAddr, stdout);
    fputc('\n', stdout);

    return clntSock;
}

// ----
int setup_tcp_server_socket(const char *service){
    /* Construct the server address structure */
    struct addrinfo addrCriteria;       // Criteria for address match
    memset(&addrCriteria, 0, sizeof(addrCriteria));
    addrCriteria.ai_family = AF_UNSPEC; // Any address family
    addrCriteria.ai_flags = AI_PASSIVE; // Accept on any address/port
    addrCriteria.ai_socktype = SOCK_STREAM;     // Only stream sockets
    addrCriteria.ai_protocol = IPPROTO_TCP;     // Only TCP protocol

    struct addrinfo *servAddr;          // List of server addresses
    int rtnVal = getaddrinfo(NULL, service, &addrCriteria, &servAddr);
    if(rtnVal != 0){
        die_with_user_message("getaddrinfo() failed", gai_strerror(rtnVal));
    }

    int servSock = -1;
    for(struct addrinfo *addr = servAddr; addr != NULL; addr = addr->ai_next){
        /* Create a TCP socket */
        servSock = socket(servAddr->ai_family, servAddr->ai_socktype,
            servAddr->ai_protocol);
        if(servSock < 0){ continue; } // Try next address
        /* Bind to the local address and set socket to list */
        if((bind(servSock, servAddr->ai_addr, servAddr->ai_addrlen) == 0) &&
            listen(servSock, MAXPENDING)==0)
        {
            struct sockaddr_storage localAddr;
            socklen_t addrSize = sizeof(localAddr);
            if(getsockname(
                servSock, (struct sockaddr*)&localAddr, &addrSize)< 0
            ){
                die_with_system_message("getsockname() failed");
            }
            fputs("Binding to ", stdout);
            print_socket_address((struct sockaddr *)&localAddr, stdout);
            fputc('\n', stdout);
            break;  // Bind and list successful
        }

        close(servSock);    // Close and try again
        servSock = -1;    
    }

    /* Free address list allocated by getaddrinfo() */
    freeaddrinfo(servAddr);
    return servSock;
}

// ----
void handle_tcp_client(int clntSocket){
    char buffer[BUFSIZ];    // Buffer for echo string

    /** Receive message from client */
    ssize_t numBytesRcvd = recv(clntSocket, buffer, BUFSIZ, 0);
    if(numBytesRcvd < 0){
        die_with_system_message("recv() failed");
    }

    /** Send received string and receive again until end of stream */
    while(numBytesRcvd > 0){ // 0 indicates end of stream
        /** Echo message back to client */
        ssize_t numBytesSent = send(clntSocket, buffer, numBytesRcvd, 0);
        if(numBytesSent < 0){
            die_with_system_message("send() failed");
        }else if(numBytesSent != numBytesRcvd){
            die_with_user_message("send()", "sent unexpected number of bytes");
        }
        /** See if there is more data to receive */
        numBytesRcvd = recv(clntSocket, buffer, BUFSIZ, 0);
        if(numBytesRcvd < 0){
            die_with_system_message("recv() failed");
        }
    }

    close(clntSocket);  // Close client socket
}

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

#include "common.h"


// -----
int main(int argc, char **argv){
    if(argc < 3 || argc > 4){ /* Test for correct number of arguments */
        die_with_user_message(
            "Parameters",
            "<Server Address> <Echo Word> [<Server Port>]"
        );
    }

    char *servIP = argv[1];     // server IP address (dotted quad)
    char *echoString = argv[2]; // string to echo

    /* Third arg (optional): server port (numeric). 7 is well-known echo port */
    in_port_t servPort = (argc == 4) ? atoi(argv[3]) : 7;

    /* Create a reliable, stream socket using TCP */
    int sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(sock < 0){
        die_with_system_message("socket() failed");
    }

    /** Construct the server address structure */
    struct sockaddr_in servAddr;            // Server address
    memset(&servAddr, 0, sizeof(servAddr)); // Zero out structure
    servAddr.sin_family = AF_INET;          // IPv4 address family

    /** Convert address */
    int rtnVal = inet_pton(AF_INET, servIP, &servAddr.sin_addr.s_addr);
    if(rtnVal == 0){
        die_with_user_message("inet_pton() failed", "invalid address string");
    }else if(rtnVal < 0){
        die_with_system_message("inet_pton() failed");
    }
    servAddr.sin_port = htons(servPort);    // Server port

    /** Establish the connection to the echo server */
    if(connect(sock, (struct sockaddr*)&servAddr, sizeof(servAddr)) < 0){
        die_with_system_message("connect() failed");
    }

    size_t echoStringLen = strlen(echoString);

    /** Send the string to the server */
    ssize_t numBytes = send(sock, echoString, echoStringLen, 0);
    if(numBytes < 0){
        die_with_system_message("send() failed");
    }else if (numBytes != echoStringLen){
        die_with_user_message("send()", "sent unexpected number of bytes");
    }

    /** Receive the same string back from the server */
    unsigned int totalBytesRcvd = 0;    // Count of total bytes received
    fputs("Received: ", stdout);        // Setup to print the echoed string
    while(totalBytesRcvd < echoStringLen){
        char buffer[BUFSIZ];            // I/O buffer
        /** Receive up to the buffer size (minus 1 to leave space for 
         * a null terminator) bytes from the sender. */
        numBytes = recv(sock, buffer, BUFSIZ-1, 0);
        if(numBytes < 0){
            die_with_system_message("recv() failed");
        }else if(numBytes == 0){
            die_with_user_message("recv()", "connection closed prematurely");
        }
        totalBytesRcvd += numBytes;     // Keep tally of total bytes
        buffer[numBytes] = '\0';        // Terminate the string!
        fputs(buffer, stdout);          // Print the echo buffer
    }

    fputc('\n', stdout);
    close(sock);

    return EXIT_SUCCESS;
}

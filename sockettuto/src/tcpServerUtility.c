#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>

#include "common.h"

//
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

#include<stdlib.h>
#include<unistd.h>

#include "common.h"

// -----
int main(int argc, char **argv){
    if(argc != 2){
        die_with_user_message("Parameter(s)", "<Server Port/Service>");
    }

    char *service = argv[1];    // local port

    /* Create socket for incoming connections */
    int servSock = setup_tcp_server_socket(service);
    if(servSock < 0){
        die_with_user_message("setup_tcp_server_socket() failed", service);
    }

    // Run forever
    for(;;){
        /* New connection creates a connected client socket */
        int clntSock = accept_tcp_connection(servSock);
        handle_tcp_client(clntSock);    // Process client
        close(clntSock);
    }

    // NOT REACHED
    return EXIT_SUCCESS;
}

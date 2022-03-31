#include<string.h>
#include<stdlib.h>
#include<unistd.h>

#include "common.h"

int main(int argc, char **argv){
    if(argc < 3 || argc > 4){
        die_with_user_message("Parameter(s)",
            "<Server Address/Name> <Echo Word> [<Server Port/Service>]");
    }

    char *server = argv[1];     // server address/name
    char *echoString = argv[2]; // string to echo
    /* OPTINAL: server port/service */
    char *service = (argc == 4) ? argv[3] : "echo";

    /* Create a connected TCP socket */
    int sock = setup_tcp_client_socket(server, service);
    if(sock < 0){
        die_with_user_message("setup_tcp_client_socket() failed",
            "unable to connect");
    }

    size_t echoStringLen = strlen(echoString);

    /* Send the string to the server */
    ssize_t numBytes = send(sock, echoString, echoStringLen, 0);
    if(numBytes < 0){
        die_with_system_message("send() failed");
    }else if(numBytes != echoStringLen){
        die_with_user_message("send()", "sent unexpected number of bytes");
    }

    /* Receive the same string back from the server */
    unsigned totalBytesRcvd = 0;    // Count of total bytes received
    fputs("Received: ", stdout);    // Setup to print the echoed string
    while(totalBytesRcvd < echoStringLen){
        char buffer[BUFSIZ];        // I/O buffer
        /* Receive up to the buffer size (minus 1 to leave space for
         * a null terminator) bytes from the sender. */
        if(numBytes < 0){
            die_with_system_message("recv() failed");
        }
        totalBytesRcvd += numBytes;     // Keep tally of total bytes
        buffer[numBytes] = '\0';        // Terminate the string
        fputs(buffer, stdout);          // Print the buffer
    }

    fputc('\n', stdout);                // Print a final linefeed
    close(sock);

    return EXIT_SUCCESS;
}

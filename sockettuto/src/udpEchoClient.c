#include<stdlib.h>
#include<string.h>

#include "common.h"

// ---
int main(int argc, char **argv){
    if(argc < 3 || argc > 4){
        die_with_user_message("Parameter(s)",
            "<Server Address/Name> <Echo Word> [<Server Port/Service>]");
    }

    char *server = argv[1];     // server address/name
    char *echoString = argv[2]; // word to echo
    size_t echoStringLen = strlen(echoString);
    if(echoStringLen > MAXSTRINGLENGTH){
        die_with_user_message(echoString, "string too long");
    }
    // OPTIONAL ARG: server port/service
    char *servPort = (argc == 4) ? argv[3] : "echo";

    // Tell the system what kind(s) of address info we want
    struct addrinfo addrCriteria; 
    memset(&addrCriteria, 0, sizeof(addrCriteria));
    addrCriteria.ai_family = AF_UNSPEC;
    addrCriteria.ai_socktype = SOCK_DGRAM;
    addrCriteria.ai_protocol = IPPROTO_UDP;

    // Get address(es)
    struct addrinfo *servAddr;
    int retVal = getaddrinfo(server, servPort, &addrCriteria, &servAddr);
    if(retVal != 0){
        die_with_user_message("getaddrinfo() failed", gai_strerror(retVal));
    }

    // Create a datagram/UDP socket
    int sock = socket(servAddr->ai_family, servAddr->ai_socktype,
        servAddr->ai_protocol); // Socket descriptor for client

    if(sock < 0){
        die_with_system_message("socket() failed");
    }

    // Send the string to the server
    ssize_t numBytes =sendto(sock, echoString, echoStringLen, 0,
        servAddr->ai_addr, servAddr->ai_addrlen);

    if(numBytes < 0){
        die_with_system_message("sendto() failed");
    }else if(numBytes != echoStringLen){
        die_with_user_message("sendto() error",
            "sent unexpected number of bytes");
    }

    // Receive a response
    struct sockaddr_storage fromAddr;   // Source address of server
    // Set length of from address structure (in-out parameter)
    socklen_t fromAddrLen = sizeof(fromAddr);
    char buffer[MAXSTRINGLENGTH+1];
    numBytes = recvfrom(sock, buffer, MAXSTRINGLENGTH, 0,
        (struct sockaddr*)&fromAddr, &fromAddrLen);

    if(numBytes < 0){
        die_with_system_message("recvfrom() failed()");
    }else if(numBytes != echoStringLen){
        die_with_user_message("recvfrom() error",
            "received unexpected number of bytes");
    }

    // Verify reception from expected source
    if(!SockAddrsEqual(servAddr->ai_addr, (struct sockaddr*)&fromAddr)){
        die_with_user_message("recvfrom()",
            "received a packet from unknown source");
    }

    freeaddrinfo(servAddr);

    buffer[echoStringLen] = '\0';
    printf("Received: %s\n", buffer);

    close(sock);

    return EXIT_SUCCESS;
}

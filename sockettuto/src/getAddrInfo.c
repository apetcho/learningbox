#include<stdlib.h>
#include<string.h>

#include "common.h"

// -------------------
// --- MAIN DRIVER ---
// -------------------
int main(int argc, char **argv){
    if(argc != 3){ // Test for correct number of arguments
        die_with_user_message("Parameter(s)", "<Address/Name> <Port/Service>");
    }

    char *addrString = argv[1];     // Server address/name
    char *portString = argv[2];     // Server port/service

    /** Tell the system what kind(s) of address info we want */
    struct addrinfo addrCriteria;   // Criteria for address match
    memset(&addrCriteria, 0, sizeof(addrCriteria));
    addrCriteria.ai_family = AF_UNSPEC;     // Any address family
    addrCriteria.ai_socktype = SOCK_STREAM; // Only stream sockect
    addrCriteria.ai_protocol = IPPROTO_TCP; // Only TCP protocol

    /** Get address(es) associated with the specified name/service */
    struct addrinfo *addrList;      // Holder for list of addresses returned
    /** Modify servAddr contents to reference linked list of addresses */
    int rtnVal = getaddrinfo(
        addrString, portString, &addrCriteria, &addrList);

    if(rtnVal != 0){
        die_with_user_message("getaddrinfo() failed", gai_strerror(rtnVal));
    }

    /** Display returned addresses */
    for(struct addrinfo *addr = addrList; addr != NULL; addr = addr->ai_next){
        print_socket_address(addr->ai_addr, stdout);
        fputc('\n', stdout);
    }

    freeaddrinfo(addrList);

    return EXIT_SUCCESS;
}

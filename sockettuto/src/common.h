#ifndef _SOCKECT_TUTORIAL_COMMON_H
#define _SOCKECT_TUTORIAL_COMMON_H
#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include <arpa/inet.h>
#include<netdb.h>


void die_with_user_message(const char *msg, const char *detail);
void die_with_system_message(const char *msg);
void handle_tcp_client(int clntSocket);
void print_socket_address(const struct sockaddr *address, FILE *stream);

#endif

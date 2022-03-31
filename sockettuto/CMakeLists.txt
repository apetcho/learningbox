cmake_minimum_required(VERSION 3.17)
project(SocketTutorial LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_executable(TCPEchoClient4 src/tcpEchoClient4.c src/dieWithMessage.c 
    src/common.h)
add_executable(TCPEchoServer4 src/tcpEchoServer4.c src/dieWithMessage.c 
    src/tcpServerUtility.c src/addressUtility.c src/common.h)

add_executable(TCPEchoServer6 src/tcpEchoServer6.c src/dieWithMessage.c 
    src/tcpServerUtility.c src/addressUtility.c src/common.h)

add_executable(TCPEchoClient6 src/tcpEchoClient6.c src/dieWithMessage.c 
    src/common.h)

add_executable(GetAddrInfo src/getAddrInfo.c src/dieWithMessage.c 
    src/addressUtility.c src/common.h)

add_executable(TCPEchoServer src/tcpEchoServer.c src/dieWithMessage.c 
    src/tcpServerUtility.c src/addressUtility.c src/common.h)

add_executable(TCPEchoClient src/tcpEchoClient.c src/dieWithMessage.c 
    src/tcpClientUtility.c src/common.h)

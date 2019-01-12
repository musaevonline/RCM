#ifndef INITIALIZATION_H
#define INITIALIZATION_H

#include <windows.h>
#ifndef NDEBUG
#include <stdio.h>
#endif

#endif

//----------------initialization-----------//
sockaddr_in *initPreConnection();
SOCKET *initConnection(sockaddr_in *addr);
char *readHeader(SOCKET *sock);
//----------------/initialization----------//

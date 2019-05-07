#ifndef SENDER_H
#define SENDER_H

#include <windows.h>
#ifndef NDEBUG
#include <stdio.h>
#endif

#endif

//-----------------sender----------------//
void sendConsoleOutput(SOCKET *sock, char * output, char *id);
void sendRequest(SOCKET *sock, char *id);
//-----------------/sender----------------//

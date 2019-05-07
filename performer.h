#ifndef PERFORMER_H
#define PERFORMER_H

#include <windows.h>
#ifndef NDEBUG
#include <stdio.h>
#endif

#endif

//-----------------performer----------------//
int execCommand(char *command);
char *readConsoleOutput(HANDLE hReadPipe);
char *readFromFile(char *fileName);
void writeToFile(char *fileName, char *str);
void closeHandles(HANDLE a1, HANDLE a2, HANDLE a3, HANDLE a4);
//-----------------/performer----------------//


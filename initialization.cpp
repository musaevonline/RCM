#include "addition.h"

sockaddr_in *initPreConnection()
{
    printf("initPreConnection\n");
    WSADATA wsadata;
    WSAStartup(MAKEWORD(1, 1), &wsadata);

    static sockaddr_in addr;
    WSAStartup(MAKEWORD(1, 1), &wsadata);
    addr.sin_family = AF_INET;
    char *addr_a;
    hostent *s = nullptr;
    while ( (s = gethostbyname("gc9515.000webhostapp.com")) == nullptr )
    {
        printf("Error connect: %d\n", WSAGetLastError());
        Sleep(LOOP_TIME_WAIT);
    }
    addr_a = inet_ntoa(*(in_addr*)s->h_addr_list[0]);
    addr.sin_addr.S_un.S_addr = inet_addr(addr_a);
    addr.sin_port = htons(80);
    //printf(inet_ntoa(*(in_addr*)gethostbyname("files.000webhost.com")->h_addr_list[0]));
    return &addr;
}

SOCKET *initConnection(sockaddr_in *addr)
{
    printf("initConnection\n");
    SOCKET *sock = nullptr;
    sock = (SOCKET*)malloc(sizeof(SOCKET));

    *sock = socket(AF_INET, SOCK_STREAM, 0);
    while ( connect(*sock, (sockaddr*)addr, sizeof(*addr)) == SOCKET_ERROR)
    {
        printf("Error connect: %d\n", WSAGetLastError());
        Sleep(RECONNECTION_TIME_WAIT);
        *sock = socket(AF_INET, SOCK_STREAM, 0);
    }
    //setsockopt(sock, SOL_SOCKET, SO_KEEPALIVE, "1", 1);
    printf("\nConnected\n");

    return sock;

}

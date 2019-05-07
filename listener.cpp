#include "addition.h"
unsigned long timeOut = time(NULL);
char *listenData(void *sock)
{
    //printf("listenData\n");
    static fd_set fd;
    int x=0;
    char *str = (char*)malloc(SIZE_PIECE_OUTPUT+1);
    ZeroMemory(str, SIZE_PIECE_OUTPUT+1);
    static timeval tv;
    tv.tv_sec = 0;
    tv.tv_usec = 0;
    FD_ZERO(&fd);
    FD_SET(*(SOCKET*)sock, &fd);
    select(*(SOCKET*)sock + 1, &fd, nullptr, nullptr, &tv);
    //printf("FD_ISSET: %d\n",FD_ISSET(*(SOCKET*)sock, &fd));
    if ( FD_ISSET(*(SOCKET*)sock, &fd) )
    {
        timeOut = time(NULL);
        if ( (x=recv(*(SOCKET*)sock, str, SIZE_PIECE_OUTPUT, 0)) == -1 || x == 0 )
        {
           // printf("%d", x);
            return nullptr;
        }
        //printf("%s", str);
        return str;
    }
    if ( time(NULL) - timeOut > 5 )
    {
        printf("%s", "timeout!\n");
        timeOut = time(NULL);
        return nullptr;
    }
    strcpy(str, "");
    return str;
}

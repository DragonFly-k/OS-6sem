#include <iostream>
#include <Windows.h>
using namespace std;

bool printFileTxt(LPWSTR FileName) {
    HANDLE fileHandle = CreateFile(FileName, GENERIC_READ, NULL, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if (fileHandle == INVALID_HANDLE_VALUE) 
        return false;
    DWORD n = NULL;
    char buf[1024];
    ZeroMemory(buf, sizeof(buf));
    bool readFile = ReadFile(fileHandle, &buf, sizeof(buf), &n, NULL);
    cout << "\nСодержимое файла:\n" << buf << endl;
    CloseHandle(fileHandle);
}

BOOL delRowFileTxt(LPWSTR FileName, DWORD row)
{
    PLARGE_INTEGER fileSize = new LARGE_INTEGER();
    int rowCount = 1;
    int position = 0;
    int positionAfter = 0;
    bool rowFound = false;
    try
    {
        if (row <= 0)
        {
            throw "Invalid number of raw";
        }
        HANDLE of = CreateFile(FileName,GENERIC_READ | GENERIC_WRITE, NULL,NULL,OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL,NULL);
        if (of == INVALID_HANDLE_VALUE)
        {
            CloseHandle(of);
            throw "Open file failed";
        }
        if (GetFileSizeEx(of, fileSize))
        {
            char* buf = new char[1024];
            char* bufAfterDel = new char[1024];
            ZeroMemory(buf, sizeof(buf));
            ZeroMemory(bufAfterDel, sizeof(bufAfterDel));
            DWORD n = NULL;
            if (ReadFile(of, buf, 1024, &n, NULL))
            {
                buf[fileSize->QuadPart] = '\0';
                while (buf[position] != '\0')
                {
                    if (buf[position] == '\n')
                    {
                        rowCount++;
                    }
                    if (rowCount == row)
                    {
                        rowFound = true;
                        rowCount++;
                        position++;
                        while (buf[position] != '\n' && buf[position] != '\0')
                        {
                            position++;
                        }
                        if (row == 1)
                        {
                            position++;
                        }
                    }
                    bufAfterDel[positionAfter++] = buf[position++];
                    if (buf[position] == '\0')
                    {
                        break;
                    }

                }
                bufAfterDel[positionAfter] = '\0';
            }
            if (rowFound)
            {
                if (SetFilePointer(of, 0, 0, FILE_BEGIN) == 0)
                {
                    if (WriteFile(of, bufAfterDel, strlen(bufAfterDel), &n, NULL))
                    {
                        cout << "\nRow deleted successfully" << endl;
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

int main()
{
    setlocale(LC_ALL, "Rus");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    LPCWSTR path = L"D:\\универ\\ос\\лабы\\1\\os9.txt";
    printFileTxt(LPWSTR(path));
    delRowFileTxt(LPWSTR(path), 1);
    printFileTxt(LPWSTR(path));
    delRowFileTxt(LPWSTR(path), 3);
    printFileTxt(LPWSTR(path)); 
    delRowFileTxt(LPWSTR(path), 8);
    printFileTxt(LPWSTR(path));
    delRowFileTxt(LPWSTR(path), 10);
    printFileTxt(LPWSTR(path));
}
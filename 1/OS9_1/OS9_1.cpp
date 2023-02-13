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

bool printFileInfo(LPWSTR FileName) {
	HANDLE fileHandle = CreateFile(FileName, GENERIC_READ, NULL, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (fileHandle == INVALID_HANDLE_VALUE) return false;
	_BY_HANDLE_FILE_INFORMATION fileInformation;
	if (!GetFileInformationByHandle(fileHandle, &fileInformation)) {
		CloseHandle(fileHandle);
		return false;
	}
	
	char filepath[20];
	wcstombs(filepath, FileName, 20);
	cout << "Имя файла: " << filepath << endl;
	
	cout << "Тип файла: ";
	DWORD fileType = GetFileType(fileHandle);
	switch (fileType) {
	case FILE_TYPE_CHAR: cout << "FILE_TYPE_CHAR" << std::endl; break;
	case FILE_TYPE_DISK: cout << "FILE_TYPE_DISK" << std::endl; break;
	case FILE_TYPE_PIPE: cout << "FILE_TYPE_PIPE" << std::endl; break;
	case FILE_TYPE_REMOTE: cout << "FILE_TYPE_REMOTE" << std::endl; break;
	case FILE_TYPE_UNKNOWN: cout << "FILE_TYPE_UNKNOWN" << std::endl; break;
	default:cout << " FILE_TYPE_UNKNOWN" << endl << endl; break;
	}

	LARGE_INTEGER lFileSize;
	BOOL bGetSize = GetFileSizeEx(fileHandle, &lFileSize);
	if (!bGetSize) return false;
	cout << "Размер файла:" << lFileSize.QuadPart << endl;
	
	FILETIME createFile = fileInformation.ftCreationTime;
	SYSTEMTIME createFileToSystemTime;
	FileTimeToSystemTime(&createFile, &createFileToSystemTime);
	SystemTimeToTzSpecificLocalTime(NULL, &createFileToSystemTime, &createFileToSystemTime);
	cout << "Дата и время создания файла:" <<"\tДата: " << createFileToSystemTime.wDay << "." << createFileToSystemTime.wMonth << "." << createFileToSystemTime.wYear
		<< "\tВремя: " << createFileToSystemTime.wHour<< ":" << createFileToSystemTime.wMinute << ":" << createFileToSystemTime.wSecond << endl;

	FILETIME lastUpdate = fileInformation.ftLastWriteTime;
	SYSTEMTIME lastUpdateToSysTime;
	FileTimeToSystemTime(&lastUpdate, &lastUpdateToSysTime);
	SystemTimeToTzSpecificLocalTime(NULL,&lastUpdateToSysTime, &lastUpdateToSysTime);
	cout << "Дата и время последнего обновления:" << "\tДата: "<< lastUpdateToSysTime.wDay << "." << lastUpdateToSysTime.wMonth << "." << lastUpdateToSysTime.wYear
		<< "\tВремя: " << lastUpdateToSysTime.wHour<< ":" << lastUpdateToSysTime.wMinute << ":" << lastUpdateToSysTime.wSecond<< endl;
	CloseHandle(fileHandle);
	return true;
}

int main() {
	setlocale(LC_ALL, "Russian");
	SetConsoleOutputCP(1251);
	LPCWSTR file = L"os9.txt";
	if (!printFileInfo(LPWSTR(file))) cout << "Error";
	if (!printFileTxt(LPWSTR(file))) cout << "Error";
	return 0;
}
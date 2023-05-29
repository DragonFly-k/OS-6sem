// OS11_CREATE.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "D:\универ\ос\лабы\3\OS111\OS11_HTAPI\HT.h"
#include <string>
#include <windows.h>
#pragma comment(lib, "OS11_HTAPI")

using namespace std;
using namespace HT;


int main(int argc, char* argv[]) // OS11_START ./files/os11_create.ht
{
	setlocale(LC_ALL, "Russian");
	try
	{
		if (argc != 2)
		{
			throw "Введите количество аргументов: 2";
		}
		const size_t cSize = strlen(argv[1]) + 1;
		wchar_t* wc = new wchar_t[cSize];
		mbstowcs(wc, argv[1], cSize);

		HTHANDLE* HT = Open(wc);
		if (HT == NULL)
		{
			throw "Хранилище не создано";
		}

		cout << "HT-Storage Start !" << endl;
		wcout << "filename = " << wc << endl;
		cout << "snapshotinterval = " << HT -> SecSnapshotInterval << endl;
		cout << "capacity = " << HT -> Capacity << endl;
		cout << "maxkeylength = " << HT -> MaxKeyLength << endl;
		cout << "maxdatalength = " << HT -> MaxPayloadLength << endl;


		while (true) {
			Sleep((HT->SecSnapshotInterval) * 1000);
			Snap(HT);
			cout << "----SNAPSHOT in Thread----" << endl;
		}
		Close(HT);
	}
	catch (const char* err)
	{
		cout << err << endl;
		exit(-1);
	}

	exit(0);
}
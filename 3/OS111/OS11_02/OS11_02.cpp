#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "D:\универ\ос\лабы\3\OS111\OS11_HTAPI\HT.h"
#include <string>
#pragma comment(lib, "OS11_HTAPI")

using namespace std;
using namespace HT;
void PrintError(char* str);

int main(int argc, char* argv[]) //OS11_02 ./files/os11_create.ht
{
	setlocale(LC_ALL, "Russian");
	srand(time(nullptr));

	try
	{
		if (argc != 2)
		{
			throw "Введите количество аргументов: 2";
		}

		const size_t cSize = strlen(argv[1]) + 1;
		wchar_t* wc = new wchar_t[cSize];
		mbstowcs(wc, argv[1], cSize);

		HTHANDLE* HT = OpenExist(wc);
		if (HT == NULL)
		{
			throw "Хранилище не создано";
		}

		string key, payload = "0";

		while (true)
		{
			Sleep(1000);

			key = to_string(rand() % 50);

			Element* element = new Element(key.c_str(), (int)key.length() + 1, payload.c_str(), (int)payload.length() + 1);
			Print(element);
			if (!Insert(HT, element))
			{
				PrintError(HT -> LastErrorMessage);
			}
			cout << "Elements amount: " << HT->ElementCount << endl;
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

void PrintError(char* str) {
	std::cout << "error: \t" << str << std::endl;
}
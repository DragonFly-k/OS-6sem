#include "HT.h"
#include <iostream>
#include <fstream>
#include <string>
#pragma warning (disable : 4996)

void PrintError(char* str);

int main()
{
	HT::HTHANDLE* HT = NULL;
	HT::HTHANDLE* HT2 = NULL;

	try {
		std::ifstream inputFile("./params.txt");
		std::ifstream inputFile2("./paramss.txt");
		int capacity, snapshotIntervalSec, maxKeyLength, maxPayloadLength;
		char fileName[256], fileName2[256];

		if (inputFile.is_open()) {
			inputFile >> capacity >> snapshotIntervalSec >> maxKeyLength >> maxPayloadLength >> fileName;
			inputFile.close();
		}
		else {return 0;}

		if (inputFile2.is_open()) {
			inputFile2 >> capacity >> snapshotIntervalSec >> maxKeyLength >> maxPayloadLength >> fileName2;
			inputFile2.close();
		}
		else {return 0;}
		
		HT = HT::Create(capacity, snapshotIntervalSec, maxKeyLength, maxPayloadLength, fileName);
		HT2 = HT::Create(capacity, snapshotIntervalSec, maxKeyLength, maxPayloadLength, fileName2);

		HT::Close(HT);
		HT::Close(HT2);

		std::cout << "-------OPEN 1-------" << std::endl;
		HT::HTHANDLE* HT1 = HT::Open(fileName);
		std::cout << "-------OPEN 2-------" << std::endl;
		HT::HTHANDLE* HT3 = HT::Open(fileName2);

		HT::Element* el1 = new HT::Element("s1", 3, "p1", 3);
		HT::Element* el2 = new HT::Element("st2", 4, "pa2", 4);

		if (!HT::Insert(HT, el1) || !HT::Insert(HT, el2) || !HT::Insert(HT2, el1) || !HT::Insert(HT2, el2)) {
			PrintError(HT::GetLastError(HT));
			PrintError(HT::GetLastError(HT2));
		}

		HT::Element* el;

		std::cout << "-------GET 1-------" << std::endl;
		if ((el = HT::Get(HT1, el1)) == NULL) PrintError(HT::GetLastError(HT1));
		else HT::Print(el);
		std::cout << "-------GET 2-------" << std::endl;
		if ((el = HT::Get(HT3, el2)) == NULL) PrintError(HT::GetLastError(HT3));
		else HT::Print(el);

		std::cout << "-------CLOSE 1-------" << std::endl;
		HT::Close(HT1);
		std::cout << "-------CLOSE 2-------" << std::endl;
		HT::Close(HT3);
	}
	catch (const char* msg)
	{
		std::cout << msg << "\n";
		if (HT != NULL) std::cout << HT::GetLastError(HT);
	}

	system("pause");
	return 0;
}
void PrintError(char* str) {
	std::cout << "error: \t" << str << std::endl;
}
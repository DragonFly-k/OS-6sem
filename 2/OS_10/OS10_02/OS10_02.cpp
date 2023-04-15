#include "HT.h"
#include <iostream>
#include <fstream>
#include <string>
#pragma warning (disable : 4996)

void PrintError(char* str);

int main()
{

	HT::HTHANDLE* HT = NULL;

	try {
		std::ifstream inputFile("./params.txt");
		int capacity, snapshotIntervalSec, maxKeyLength, maxPayloadLength;
		char fileName[256];

		if (inputFile.is_open()) {
			inputFile >> capacity >> snapshotIntervalSec >> maxKeyLength >> maxPayloadLength >> fileName;
			inputFile.close();
		}
		else {
			return 0;
		}

		HT = HT::Create(capacity, snapshotIntervalSec, maxKeyLength, maxPayloadLength, fileName);
		if (HT) std::cout << "Create: success\n";
		else throw "Create: error";

		HT::Element* el1 = new HT::Element("s1", 3, "p1", 3);
		HT::Element* el2 = new HT::Element("st2", 4, "pa2", 4);
		HT::Element* el3 = new HT::Element("str3", 5, "pay3", 5);

		if (!HT::Insert(HT, el1) || !HT::Insert(HT, el2) || !HT::Insert(HT, el3)) {
			PrintError(HT::GetLastError(HT));
		}

		HT::Element* el;
		std::cout << "\n-------INSERT------\n" << std::endl;
		if ((el = HT::Get(HT, el1)) == NULL) PrintError(HT::GetLastError(HT));
		else HT::Print(el);
		if ((el = HT::Get(HT, el2)) == NULL) PrintError(HT::GetLastError(HT));
		else HT::Print(el);
		if ((el = HT::Get(HT, el3)) == NULL) PrintError(HT::GetLastError(HT));
		else HT::Print(el);


		if (!HT::Update(HT, el1, el3->payload, el3->payloadlength)) {
			PrintError(HT::GetLastError(HT));
		}
		if (!HT::Update(HT, el2, el3->payload, el3->payloadlength)) {
			PrintError(HT::GetLastError(HT));
		}

		if (!HT::Snap(HT))
			PrintError(HT::GetLastError(HT));

		std::cout << "\n-------UPDATE-------\n" << std::endl;
		if ((el = HT::Get(HT, el1)) == NULL) PrintError(HT::GetLastError(HT));
		else HT::Print(el);
		if ((el = HT::Get(HT, el2)) == NULL) PrintError(HT::GetLastError(HT));
		else HT::Print(el);
		if ((el = HT::Get(HT, el3)) == NULL) PrintError(HT::GetLastError(HT));
		else HT::Print(el);

		if (!HT::Delete(HT, el2)) {
			PrintError(HT::GetLastError(HT));
		}
		if (!HT::Delete(HT, el3)) {
			PrintError(HT::GetLastError(HT));
		}

		std::cout << "\n-------DELETE-------\n" << std::endl;
		if ((el = HT::Get(HT, el1)) == NULL) PrintError(HT::GetLastError(HT));
		else HT::Print(el);
		if ((el = HT::Get(HT, el3)) == NULL) PrintError(HT::GetLastError(HT));
		else HT::Print(el);

		std::cout << "\n-------CLOSE-------\n" << std::endl;
		HT::Close(HT);
		std::cout << "\n-------OPEN-------\n" << std::endl;

		HT::HTHANDLE* HT2 = HT::Open(fileName);
		std::cout << "\n-------GET-------\n" << std::endl;
		if ((el = HT::Get(HT2, el1)) == NULL) PrintError(HT::GetLastError(HT));
		else HT::Print(el);

		std::cout << "\n-------CLOSE-------\n" << std::endl;
		HT::Close(HT2);
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
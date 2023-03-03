#include <Windows.h>
#include <iostream>
#include "HT.h"
using namespace std;

void printStr(char* str);

int main()
{
	try {
		const wchar_t* fileName = L"D:\\универ\\ос\\лабы\\2\\HT\\1.ht";
		HT::HTHANDLE* HT = HT::Create(10, 2, 10, 10, fileName);
		if (HT == NULL) throw "Invalid handle";

		HT::Element* el1 = new HT::Element("OS1", 4, "ere;l;;r", 10);
		HT::Element* el2 = new HT::Element("OS12", 5, "dfk;4jlj", 9);
		HT::Element* el3 = new HT::Element("OS123", 6, "mgdlk;;", 8);
		HT::Element* el4 = new HT::Element("OS1234", 7, "kfllgf", 7);

		//INSERT 
		if (!HT::Insert(HT, el1)) {
			printStr(HT::GetLastError(HT));
		}
		if (!HT::Insert(HT, el2)) {
			printStr(HT::GetLastError(HT));
		}
		if (!HT::Insert(HT, el3)) {
			printStr(HT::GetLastError(HT));
		}
		if (!HT::Insert(HT, el4)) {
			printStr(HT::GetLastError(HT));
		}

		//GET AFTER INSERT
		HT::Element* el;
		std::cout << "-----INSERT-----" << std::endl;
		if ((el = HT::Get(HT, el1)) == NULL) printStr(HT::GetLastError(HT));
		else HT::print(el);
		if ((el = HT::Get(HT, el2)) == NULL) printStr(HT::GetLastError(HT));
		else HT::print(el);
		if ((el = HT::Get(HT, el3)) == NULL) printStr(HT::GetLastError(HT));
		else HT::print(el);
		if ((el = HT::Get(HT, el4)) == NULL) printStr(HT::GetLastError(HT));
		else HT::print(el);

		//UPDATE
		if (!HT::Update(HT, el1, el3->payload, el3->payloadlength)) {
			printStr(HT::GetLastError(HT));
		}
		if (!HT::Update(HT, el4, el3->payload, el3->payloadlength)) {
			printStr(HT::GetLastError(HT));
		}

		//SNAP
		if (!HT::Snap(HT))
			printStr(HT::GetLastError(HT));
		std::cout << "-----UPDATE-----" << std::endl;
		//GET AFTER UPDATE
		if ((el = HT::Get(HT, el1)) == NULL) printStr(HT::GetLastError(HT));
		else HT::print(el);
		if ((el = HT::Get(HT, el2)) == NULL) printStr(HT::GetLastError(HT));
		else HT::print(el);
		if ((el = HT::Get(HT, el3)) == NULL) printStr(HT::GetLastError(HT));
		else HT::print(el);
		if ((el = HT::Get(HT, el4)) == NULL) printStr(HT::GetLastError(HT));
		else HT::print(el);

		Sleep(10000);
		//DELETE
		if (!HT::Delete(HT, el2)) {
			printStr(HT::GetLastError(HT));
		}
		if (!HT::Delete(HT, el4)) {
			printStr(HT::GetLastError(HT));
		}

		//GET AFTER DELETE
		std::cout << "-----DELETE-----" << std::endl;
		if ((el = HT::Get(HT, el1)) == NULL) printStr(HT::GetLastError(HT));
		else HT::print(el);
		if ((el = HT::Get(HT, el2)) == NULL) printStr(HT::GetLastError(HT));
		else HT::print(el);
		if ((el = HT::Get(HT, el3)) == NULL) printStr(HT::GetLastError(HT));
		else HT::print(el);
		if ((el = HT::Get(HT, el4)) == NULL) printStr(HT::GetLastError(HT));
		else HT::print(el);


		HT::Close(HT);
		//GET AFTER DELETE
		HT::HTHANDLE* HT2 = HT::Open(fileName);
		std::cout << "-----GET-----" << std::endl;
		if ((el = HT::Get(HT, el1)) == NULL) printStr(HT::GetLastError(HT));
		else HT::print(el);
		if ((el = HT::Get(HT, el2)) == NULL) printStr(HT::GetLastError(HT));
		else HT::print(el);
		if ((el = HT::Get(HT, el3)) == NULL) printStr(HT::GetLastError(HT));
		else HT::print(el);
		if ((el = HT::Get(HT, el4)) == NULL) printStr(HT::GetLastError(HT));
		else HT::print(el);

		HT::Close(HT2);
		delete el1;
		delete el2;
		delete el3;
		delete el4;
		delete el;
	}
	catch (const char* mess) {
		std::cout << mess << std::endl;
	}

	system("pause");
	return 0;
}
void printStr(char* str) {
	std::cout << "ERROR:\t" << str << std::endl;
}
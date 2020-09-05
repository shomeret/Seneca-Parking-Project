#define _CRT_SECURE_NO_WARNINGS
#include <cstring>
#include <cctype>
#include <iostream>
#include "Utils.h"
// [] {} || \n < > << >> ""
using namespace std;

//Name: Alan Yanovich
//St#: 021278106
//email: ayanovich@myseneca.ca
//date: Aug 4, 2020



namespace sdds {
	void Utils::read(int& val, int min, int max, const char* ErrorMess) {
		bool ok;
		char newline;
		const char* orgMes = ErrorMess;
		const char invalidInt[] = "Invalid Integer, try again: ";
		do {
			cin >> val;
			newline = cin.get();
			if (cin.fail() || newline != '\n') {
				ok = false;
				cin.clear();
				cin.ignore(1000, '\n');
				ErrorMess = invalidInt;
			}
			else {
				ok = val <= max && val >= min;
				ErrorMess = orgMes;
			}
		} while (!ok && cout << ErrorMess);
	}

	char Utils::yesOrNo() {
		char letter[20];
		cin >> letter;
		letter[0] = toupper(letter[0]);
		// for (letter[0] = toupper(letter[0]); letter[0] != 'Y' && letter[0] != 'N'; letter[0] = toupper(letter[0])) 
		while ((letter[0] != 'Y' && letter[0] != 'N') || strlen(letter) > 1) {
			cout << "Invalid response, only (Y)es or (N)o are acceptable, retry: ";
			cin >> letter;
			letter[0] = toupper(letter[0]);
		} 
		return letter[0];
	}
}

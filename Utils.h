#ifndef SDDS_UTILS_H
#define SDDS_UTILS_H
#include <iostream>

//Name: Alan Yanovich
//St#: 021278106
//email: ayanovich@myseneca.ca
//date:  Aug 4, 2020



namespace sdds {
	const unsigned int ReadBufferSize = 40;
	struct Utils {
		static void read(int& val, int min, int max, const char* errorMessage = "");
		static char yesOrNo();
	};
	
}




#endif


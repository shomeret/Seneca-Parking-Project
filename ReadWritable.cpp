#include "ReadWritable.h"

// || >> << "" ? '' \0 [] {}
 //Name: Alan Yanovich
 //St#: 021278106
 //email: ayanovich@myseneca.ca
 //date: Aug 4, 2020


namespace sdds {
	ReadWritable::ReadWritable():csvFlag(false) {}

	ReadWritable::~ReadWritable(){}

	bool ReadWritable::isCsv() const {
		return csvFlag;
	}

	void ReadWritable::setCsv(bool value) {
		csvFlag = value;
	}

	std::ostream& operator<<(std::ostream& os, const ReadWritable& rw) {
		rw.write(os);
		return os;
	}
	std::istream& operator>>(std::istream& is, ReadWritable& rw) {
		rw.read(is);
		return is;
		
	}
}
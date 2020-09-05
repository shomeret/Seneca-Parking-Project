#ifndef _SDDS_READWRITABLE_H
#define _SDDS_READWRITABLE_H
#include <iostream>

// || >> << "" ? '' \0 [] {}
 //Name: Alan Yanovich
 //St#: 021278106
 //email: ayanovich@myseneca.ca
 //date:  Aug 4, 2020



namespace sdds {
	class ReadWritable {
	public:
		ReadWritable();
		virtual ~ReadWritable();
		bool isCsv() const;
		void setCsv(bool value);
		virtual std::istream& read(std::istream& in = std::cin) = 0;
		virtual std::ostream& write (std::ostream& is = std::cout) const = 0;
	private:
		bool csvFlag;
	};


	std::ostream& operator<<(std::ostream& os, const ReadWritable& rw);
	std::istream& operator>>(std::istream& is, ReadWritable& rw);


}









#endif
#ifndef SDDS_MOTORCYCLE_H
#define SDDS_MOTORCYCLE_H
#include "Vehicle.h"

// || >> << "" ? '' \0 [] {}
//Name: Alan Yanovich
//St#: 021278106
//email: ayanovich@myseneca.ca
//date:  Aug 4, 2020

namespace sdds {
	class Motorcycle:public Vehicle {
	public:
		Motorcycle();
		Motorcycle(const char* license, const char* makeMod);
		Motorcycle(const Motorcycle& source) = delete;
		Motorcycle& operator=(const Motorcycle& soruce) = delete;
		std::istream& read(std::istream& in = std::cin) override;
		std::ostream& write(std::ostream& is = std::cout) const override;
	private:
		bool sideCarFlag;
	};


}

#endif
#ifndef SDDS_CAR_H
#define SDDS_CAR_H
#include "Vehicle.h"

// || >> << "" ? '' \0 [] {}
//Name: Alan Yanovich
//St#: 021278106
//email: ayanovich@myseneca.ca
//date:  Aug 4, 2020

namespace sdds {
	class Car:public Vehicle {
	public:
		Car();
		Car(const char* license, const char* makeMod);
		Car(const Car& source) = delete;
		Car& operator=(const Car& soruce) = delete;
		std::istream& read(std::istream& in = std::cin) override;
		std::ostream& write(std::ostream& is = std::cout) const override;
		bool washStat();
	private:
		bool carWashFlag;
	};






}











#endif
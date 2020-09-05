#include <ios>
#include <iostream>
#include <string>
#include <limits>
#include "Car.h"
#include "Vehicle.h"
#include "Utils.h"

// || >> << "" ? '' \0 [] {}
//Name: Alan Yanovich
//St#: 021278106
//email: ayanovich@myseneca.ca
//date:  Aug 4, 2020


namespace sdds {
	// Constructors of Car
	Car::Car()
	:Vehicle(), carWashFlag{false}{ ; }

	Car::Car(const char* license, const char* makeMod)
	:Vehicle(license, makeMod), carWashFlag{ false }{ ; }

	//Public read and write functions
	std::istream& Car::read(std::istream& in) {
		if (isCsv()) {
			// from a csv file
			Vehicle::read(in);
			in >> carWashFlag;
			in.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
		} else {
			//interactive
			std::cout << std::endl;
			std::cout << "Car information entry" << std::endl;
			Vehicle::read(in); 
			std::cout << "Carwash while parked? (Y)es/(N)o: ";
			char yOrN = Utils::yesOrNo();
			if (yOrN == 'Y')
				carWashFlag = true;
			else
				carWashFlag = false;
		}
		return in;
	}







	std::ostream& Car::write(std::ostream& is) const {
		if (isEmpty()) {
			is << "Invalid Car Object" << std::endl;
			return is;
		}
		if (isCsv()) {
			is << "C,";
		} else {
			is << "Vehicle type: Car" << std::endl;
		}
		Vehicle::write(is);
		if (isCsv()) {
			is << carWashFlag << std::endl;
		} else {
			if (carWashFlag)
				is << "With Carwash" << std::endl;
			else
				is << "Without Carwash" << std::endl;
		}
		return is;
	}

	bool Car::washStat() {
		return carWashFlag;
	}
} // namespace sdds

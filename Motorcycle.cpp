#include <ios>
#include <iostream>
#include <string>
#include <limits>
#include "Motorcycle.h"
#include "Utils.h"

// || >> << "" ? '' \0 [] {}
//Name: Alan Yanovich
//St#: 021278106
//email: ayanovich@myseneca.ca
//date:  Aug 4, 2020


namespace sdds {
	// Constructors of Motorcycle
	Motorcycle::Motorcycle()
		:Vehicle(), sideCarFlag{ false }{; }

	Motorcycle::Motorcycle(const char* license, const char* makeMod)
		: Vehicle(license, makeMod), sideCarFlag{ false }{; }

	//Public read and write functions
	std::istream& Motorcycle::read(std::istream& in) {
		if (isCsv()) {
			// from a csv file
			Vehicle::read(in);
			in >> sideCarFlag;
			in.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // question
		}
		else {
			//interactive
			std::cout << std::endl;
			std::cout << "Motorcycle information entry" << std::endl;
			Vehicle::read(in);
			std::cout << "Does the Motorcycle have a side car? (Y)es/(N)o: ";
			char yOrN = Utils::yesOrNo();
			if (yOrN == 'Y')
				sideCarFlag = true;
			else
				sideCarFlag = false;
		}
		return in;
	}




	std::ostream& Motorcycle::write(std::ostream& is) const {
		if (isEmpty()) {
			is << "Invalid Motorcycle Object" << std::endl;
			return is;
		}
		if (isCsv()) {
			is << "M,";
		}
		else {
			is << "Vehicle type: Motorcycle" << std::endl;
		}
		Vehicle::write(is);
		if (isCsv()) {
			is << sideCarFlag << std::endl;
		}
		else {
			if (sideCarFlag)
				is << "With Sidecar" << std::endl;
		}
		return is;
	}
} // namespace sdds

#define _CRT_SECURE_NO_WARNINGS
#include <cstring>
#include <cctype>
#include <cstdio>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>
#include "Vehicle.h"

// || >> << "" ? '' \0 [] {}

//Name: Alan Yanovich
//St#: 021278106
//email: ayanovich@myseneca.ca
//date: Aug 4, 2020




namespace sdds {
	// Constructors and destructor of Vehicle
	Vehicle::Vehicle() {
		licenseP[0] = '\0';
		makeModel = nullptr;
		parkSpot = INVALID_PARKING_SPACE;
	}
	Vehicle::Vehicle(const char* license, const char* makeMod) {
		if (license == nullptr || '\0' == license[0] || strlen(license) > 8 ||
			makeMod == nullptr || strlen(makeMod) < 3) {
			licenseP[0] = '\0';
			makeModel = nullptr;
			parkSpot = INVALID_PARKING_SPACE;
		} else {
			const auto licenseLen = strlen(license);
			strncpy(licenseP, license, licenseLen + 1);
			strtoupper(licenseP);

			const auto makeModLen = strlen(makeMod);
			makeModel = new char[makeModLen + 1];
			strcpy(makeModel, makeMod);

			parkSpot = 0;
		}
	}

	Vehicle::~Vehicle() {
		delete[] makeModel;
	}
	
	// Public members of Vehicle

	int Vehicle::getParkingSpot() const{
		return parkSpot;
	}

	void Vehicle::setParkingSpot(int newVal) {
		if (newVal < 0) {
			setEmpty();
		} else
			parkSpot = newVal;
	}

	bool Vehicle::operator==(const char* licensePlate) const {
		if (licensePlate == nullptr)
			return false;

		std::string str(licensePlate);
		std::string str2(licenseP);

		std::transform(str.begin(), str.end(), str.begin(), ::toupper);
		std::transform(str2.begin(), str2.end(), str2.begin(), ::toupper);

		 if (str == str2)
			return true;
		 
		 return false;
	}
	
	bool Vehicle::operator==(const Vehicle& vehicle) const {
		return (*this) == vehicle.licenseP;
	}


	std::istream& Vehicle::read(std::istream& in) {
		delete[] makeModel;
		makeModel = nullptr;
		if (isCsv()) {
			char temp[61] = { '\0' };
			// from a csv file
			in >> parkSpot;
			in.ignore(1, ',').getline(licenseP, 9, ',');
			strtoupper(licenseP);
			in.getline(temp, 61, ',');
			makeModel = new char[strlen(temp) + 1];
			strcpy(makeModel, temp);
		} else {
			// interactive
			std::cout << "Enter Licence Plate Number: ";
			std::string textInput;
			std::getline(in, textInput);
			while (textInput.size() > 8 || textInput.empty()) {
				std::cout << "Invalid Licence Plate, try again: ";
				std::getline(in, textInput);
			}
			strcpy(licenseP, textInput.c_str());
			strtoupper(licenseP);

			char tempTwo[61] = { '\0' };
			std::cout << "Enter Make and Model: ";
			in.getline(tempTwo, 61, '\n');
			while (strlen(tempTwo) < 2 || strlen(tempTwo) > 60) {
				std::cout << "Invalid Make and model, try again: ";
				in.getline(tempTwo, '\n');
			}
			makeModel = new char[strlen(tempTwo) + 1]; 
			strcpy(makeModel, tempTwo);
			parkSpot = 0;
		}

		if (in.fail()) {
			setEmpty();
		}


		return in;
	}

	std::ostream& Vehicle::write(std::ostream& is) const {
		if (makeModel == nullptr) {
			is << "Invalid Vehicle Object" << std::endl;
			return is;
		} else {
			if (isCsv()) {
				is << parkSpot << "," << licenseP << "," << makeModel << ",";
			} else {
				is << "Parking Spot Number: ";
				if (parkSpot > 0)
					is << parkSpot;
				else
					is << "N/A";

				is << std::endl;
				is << "Licence Plate: " << licenseP << std::endl;
				is << "Make and Model: " << makeModel << std::endl;
			}

		
		}

		return is;
	}


	void Vehicle::strtoupper(char* src)
	{
		for (; *src; ++src) {
			*src = toupper(*src);
		}
	}
	// Protected members of Vehicle

	void Vehicle::setEmpty() {
		licenseP[0] = '\0';
		delete[] makeModel;
		makeModel = nullptr; 
		parkSpot = INVALID_PARKING_SPACE;
	}
	
	bool Vehicle::isEmpty() const {
		return (makeModel == nullptr);
	}

	const char* Vehicle::getLicensePlate() const { 
		return licenseP;
	}

	const char* Vehicle::getMakeModel() const { 
		return makeModel;
	}

	void Vehicle::setMakeModel(const char* newVal) {
		if (newVal == nullptr || '\0' == newVal[0])
			setEmpty();
		else {
			delete[] makeModel;
			const auto makeModLen = strlen(newVal);
			makeModel = new char[makeModLen + 1];
			strcpy(makeModel, newVal);
		}
	}
}
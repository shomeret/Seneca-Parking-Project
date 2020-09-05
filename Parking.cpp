#define _CRT_SECURE_NO_WARNINGS
#include <cstring>
#include <cctype>
#include <cstdio>
#include <string>
#include <iomanip>  
#include <cstring>
#include <iostream>
#include <fstream>
#include <algorithm>
#include "Parking.h"
#include "Menu.h"
#include "Utils.h"
// [] {} || \n <  << >> ""

 //Name: Alan Yanovich
 //St#: 021278106
 //email: ayanovich@myseneca.ca
 //date: Aug 4, 2020



namespace sdds {
	// Parking constructor and destructor

	Parking::Parking(const char* filename, int noOfSpots) :
		_parkingMenu("Parking Menu, select an action:"),
		_vehicleMenu("Select type of the vehicle:", 1)
	{
		for (int i = 0; i < maxParkSpot; i++) {
			_parkingSpots[i] = nullptr;
		}
		if (filename == nullptr || '\0' == filename[0]
			|| maxParkSpot < noOfSpots || 10 > noOfSpots) {
			_filename = nullptr; // signifies invalid empty state
			_numOfParkSpots = 0;
			_currentParked = 0;
		}
		else {
			const auto len = strlen(filename);
			_filename = new char[len + 1];
			strncpy(_filename, filename, len + 1);
			_numOfParkSpots = noOfSpots; // Add parking spot
			_currentParked = 0;
			if (loadDataFile()) {
				_vehicleMenu.add("Car"); // vehicleMenu
				_vehicleMenu.add("Motorcycle");
				_vehicleMenu.add("Cancel");
				_parkingMenu.add("Park Vehicle"); // parkingMenu
				_parkingMenu.add("Return Vehicle");
				_parkingMenu.add("List Parked Vehicles");
				_parkingMenu.add("Close Parking (End of day)");
				_parkingMenu.add("Exit Program");
			}
			else {
				std::cout << "Error in data file" << std::endl;
				delete[] _filename;
				_filename = nullptr;
				_numOfParkSpots = 0;
				_currentParked = 0;
			}
		}

	}

	Parking::~Parking() {
		if (!isEmpty()) {
			saveDataFile();
			delete[] _filename;
			_filename = nullptr;
			for (int i = 0; i < _numOfParkSpots && _currentParked > 0; i++) {
				if (_parkingSpots[i] != nullptr) {
					delete _parkingSpots[i];
					_parkingSpots[i] = nullptr;
					_currentParked--;
				}
			}
		}
	}


	bool Parking::isEmpty() const {
		if (_filename == nullptr)
			return true;
		else
			return false;
	}

	void Parking::strtoupper(char* src)
	{
		for (; *src; ++src) {
			*src = toupper(*src);
		}
	}

	// Parking help functions 

	void Parking::parkingStatus() const {
		std::cout << "****** Seneca Valet Parking ******" << std::endl;
		std::cout << "*****  Available spots: ";
		std::cout.width(4);
		std::cout << std::left << _numOfParkSpots - _currentParked;
		std::cout << " *****" << std::endl;
	}


	void Parking::park(Vehicle& vehicle) {
		bool exitLoop = false;
		vehicle.setCsv(false);
		vehicle.read();
		for (int i = 0; i < _numOfParkSpots && exitLoop == false; i++) {
			if (_parkingSpots[i] == nullptr) {
				vehicle.setParkingSpot(i + 1);
				std::cout << "\nParking Ticket" << std::endl;
				vehicle.write();
				_parkingSpots[i] = &vehicle;
				_currentParked++;
				std::cout << std::endl;
				exitLoop = true;
			}
		}
	}

	void Parking::parkVehicle() {
		if (_currentParked == _numOfParkSpots) {
			std::cout << "Parking is full" << std::endl;
			return; //exit
		}
		int choice{ _vehicleMenu.run() };
		switch (choice) {
		case 1: {
			//std::cout << "Parking Car" << std::endl;

			auto myNewCar = new Car;
			park(*myNewCar);

			break;
		}
		case 2:
		{
			//std::cout << "Parking Motorcycle" << std::endl;

			auto myMoto = new Motorcycle;
			park(*myMoto);

			break;
		}
		case 3:
		{
			std::cout << "Parking cancelled" << std::endl;
			break;
		}
		}
	}

	void Parking::returnVehicle() {
		std::cout << "Return Vehicle" << std::endl;
		std::cout << "Enter Licence Plate Number: ";
		std::cin.ignore();
		char txtInput[10] = { '\0' };
		std::cin.getline(txtInput, 9);
		while (strlen(txtInput) > 8 || strlen(txtInput) < 1) {
			std::cout << "Invalid Licence Plate, try again: ";
			std::cin.ignore(1000, '\n');
			std::cin.getline(txtInput, 9);
		}
		strtoupper(txtInput);
		std::cout << std::endl;
		bool foundCar = false;
		for (int i = 0; i < _numOfParkSpots && !foundCar; i++) {
			if (_parkingSpots[i] != nullptr) {
				if (strcmp(txtInput, _parkingSpots[i]->getLicensePlate()) == 0) {
					std::cout << "Returning: " << std::endl;
					_parkingSpots[i]->setCsv(false);
					_parkingSpots[i]->write();
					delete _parkingSpots[i];
					_parkingSpots[i] = nullptr;
					_currentParked--;
					std::cout << std::endl;
					foundCar = true;
				}


			}

		}
		if (!foundCar)
			std::cout << "License plate " << txtInput << " Not found" << std::endl;

	}


	void Parking::listParkedVehicle() const {
		std::cout << "*** List of parked vehicles ***" << std::endl;
		for (int i = 0; i < _numOfParkSpots; i++) {
			if (_parkingSpots[i] != nullptr) {
				_parkingSpots[i]->setCsv(false);
				_parkingSpots[i]->write();
				std::cout << std::string(31, '-') << std::endl;
			}
		}
	}

	bool Parking::closeParking() {
		if (isEmpty()) {
			std::cout << "Closing Parking" << std::endl;
			return true;
		}
		Utils util;
		char yOrN;
		std::cout << "This will Remove and tow all remaining vehicles from the parking!" << std::endl;
		std::cout << "Are you sure? (Y)es/(N)o: ";
		yOrN = util.yesOrNo();
		if (yOrN == 'N') {
			std::cout << "Aborted!" << std::endl;
			return false;
		}
		else {
			std::cout << "Closing Parking" << std::endl;
			for (int i = 0; i < _numOfParkSpots; i++) {
				if (_parkingSpots[i] != nullptr) {
					_parkingSpots[i]->setCsv(false);
					std::cout << "\nTowing request" << std::endl;
					std::cout << "*********************" << std::endl;
					_parkingSpots[i]->write();
					delete _parkingSpots[i];
					_parkingSpots[i] = nullptr;
					_currentParked--;
				}
			}
		}
		std::cin.ignore(1000, '\n');
		return true;
	}
	bool Parking::exitParkingApp() {
		Utils util;
		char yOrN;
		std::cout << "This will terminate the program!" << std::endl;
		std::cout << "Are you sure? (Y)es/(N)o: ";
		yOrN = util.yesOrNo();
		if (yOrN == 'Y') {
			std::cout << "Exiting program!" << std::endl;
			std::cin.ignore(1000, '\n');
			return true;
		}
		return false;

	}

	bool Parking::loadDataFile() {
		bool success{ true };
		if (!isEmpty()) {
			std::ifstream fin;
			fin.open(_filename);

			if (fin.is_open()) {
				// if in good state then:
				while (fin.good() && success && _currentParked < _numOfParkSpots) {
					char cOrM = 0;
					fin.get(cOrM);
					if (fin.good()) {
						fin.ignore(1);
						Vehicle* vehicle = nullptr;
						success = false;
						if ('C' == cOrM) {
							vehicle = new Car;
							success = true;
						}
						else if ('M' == cOrM) {
							vehicle = new Motorcycle;
							success = true;
						}
						if (success) {
							vehicle->setCsv(true);
							vehicle->read(fin);
							if (vehicle->isEmpty()) {
								delete vehicle;
								vehicle = nullptr;
								success = false;
							}
							else {
								int parkNum = (vehicle->getParkingSpot() - 1);
								_parkingSpots[parkNum] = vehicle;
								_currentParked++;
							}
						}
						else {
							success = false;
							delete vehicle;
							vehicle = nullptr;
						}
					}
				}
			}
		}

		return success;
	}

	void Parking::saveDataFile() {
		std::ofstream fos;
		fos.open(_filename);
		if (fos.is_open()) {
			for (int i = 0; i < _numOfParkSpots; i++) {
				if (_parkingSpots[i] != nullptr) {
					_parkingSpots[i]->setCsv(true);
					_parkingSpots[i]->write(fos);
				}
			}
		}
		
	}

	// Parking public functions


	int Parking::run() {
		// state checking
		if (isEmpty()) {
			return 1;
		}

		int choice;
		auto parkingOpen = true;
		while (parkingOpen) {
			parkingStatus();
			_parkingMenu.display();
			std::cin >> choice;
			switch (choice) {
			case 1:
				parkVehicle();
				break;
			case 2:
				returnVehicle();
				break;
			case 3:
				listParkedVehicle();
				break;
			case 4:
				if (closeParking())
					parkingOpen = false;
				break;
			case 5:
				if (exitParkingApp())
					parkingOpen = false;
				break;
			}
		}

		return 0;
	}
}

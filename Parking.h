#ifndef SDDS_PARKING_H
#define SDDS_PARKING_H
#include "Menu.h"
#include "Vehicle.h"
#include "Car.h"
#include "Motorcycle.h"
#include "Utils.h"
// [] {} || \n < > << >> ""

 //Name: Alan Yanovich
 //St#: 021278106
 //email: ayanovich@myseneca.ca
 //date: Aug 4, 2020


namespace sdds {
	const int maxParkSpot = 100;
	class Car;
	class Motorcycle;
	class Vehicle;
	class Menu;
	class Parking {
	public:
		// static const int maxParkSpot = 100;
		int run();
		Parking(const char*, int);
		~Parking();
		Parking(const Parking& source) = delete;
		Parking& operator=(const Parking& source) = delete;
	private:
		bool isEmpty() const;
		void parkingStatus() const;
		void parkVehicle();
		void returnVehicle();
		void listParkedVehicle() const;
		bool closeParking();
		bool exitParkingApp();
		bool loadDataFile();
		void saveDataFile();
		void park(Vehicle& vehicle);
		static void strtoupper(char* src);



		int _numOfParkSpots;
		Vehicle* _parkingSpots[maxParkSpot];
		int _currentParked; // always less than numOfParkSpot
		char* _filename;
		Menu _parkingMenu;
		Menu _vehicleMenu;

	};


}



#endif


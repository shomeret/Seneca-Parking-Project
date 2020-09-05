#ifndef SDDS_VEHICLE_H
#define SDDS_VEHICLE_H
#include "ReadWritable.h"

// || >> << "" ? '' \0 [] {}
//Name: Alan Yanovich
//St#: 021278106
//email: ayanovich@myseneca.ca
//date:  Aug 4, 2020

namespace sdds {
	class Vehicle:public ReadWritable {
	public:
	#define INVALID_PARKING_SPACE (-1)
		Vehicle();
		Vehicle(const char* license, const char* makeMod);
		Vehicle(const Vehicle& source) = delete;
		Vehicle& operator=(const Vehicle& source) = delete;
		virtual ~Vehicle();
		int getParkingSpot() const;
		void setParkingSpot(int newVal);
		bool operator==(const char* licensePlate) const; 
		bool operator==(const Vehicle& vehicle) const; 
		std::istream& read(std::istream& in = std::cin);
		std::ostream& write(std::ostream& is = std::cout) const;
		const char* getLicensePlate() const;
		const char* getMakeModel() const;
		bool isEmpty() const;
		void strtoupper(char* src);
	protected:
		void setEmpty();
		void setMakeModel(const char* newVal);
	private:
		char licenseP[9];
		char* makeModel;
		int parkSpot;


	};





}










#endif
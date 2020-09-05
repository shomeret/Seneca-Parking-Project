#ifndef SDDS_MENU_H
#define SDDS_MENU_H
#include <iostream>

// [] {} || \n < > << >> ""

 //Name: Alan Yanovich
 //St#: 021278106
 //email: ayanovich@myseneca.ca
 //date: Jul 16, 2020



namespace sdds {
	const int MAX_NO_OF_ITEMS = 10;
	class MenuItem;
	class Menu {
		char* MenuTitle;
		MenuItem* menuitems[MAX_NO_OF_ITEMS];
		int total_items;
		int title_length;
		int indentation;
	public:
		Menu();
		Menu(const char* item, int indent = 0);
		Menu(const Menu& source);
		~Menu();
		Menu& operator=(const Menu& source);
		Menu& operator=(const char* string);
		operator bool() const;
		void delMenu();
		void printSpace() const;
		void delMenuItems();
		void delMenuTitle();
		bool isEmpty() const;
		void display() const;
		void add(const char* item);
		bool isValid() const;
		void emptyState();
		Menu& operator<<(const char* string);
		int run() const;
		operator int()const;
	};

	class MenuItem {
		friend class Menu;
		char* Menuitem;
		MenuItem(const char*);
		void item_display() const;
		MenuItem(const MenuItem& source) = delete;
		MenuItem& operator=(const MenuItem& source) = delete;
		~MenuItem();
	};
	//std::ostream& operator<<(std::ostream& os, const MenuItem& mi);
	//std::istream& operator>>(std::istream& is, MenuItem& mi);

}




#endif

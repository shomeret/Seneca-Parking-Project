#define _CRT_SECURE_NO_WARNINGS
#include <cstring>
#include <cctype>
#include <cstdio>
#include <string>
#include <cstring>
#include <iostream>
#include <iomanip>
#include "Menu.h"
#include "Utils.h"

// [] {} || \n < > << >> ""

 //Name: Alan Yanovich
 //St#: 021278106
 //email: ayanovich@myseneca.ca
 //date: Aug 4, 2020




namespace sdds {
	MenuItem::MenuItem(const char* item) {
		if (item == nullptr) {
			Menuitem = nullptr;
		} else {
			Menuitem = new char[strlen(item)+1];
			strcpy(Menuitem, item);
		}
	}
	
	void MenuItem::item_display() const {
		if (Menuitem != nullptr)
			std::cout << Menuitem;
	}

	MenuItem::~MenuItem() {
		delete[] Menuitem;
		//Menuitem = nullptr;
	}
	
	
	// starting Menu

	Menu::Menu() {
		emptyState();
	}


	void Menu::delMenuTitle() { 
		if (MenuTitle) {
			delete[] MenuTitle;
			MenuTitle = nullptr;
		}
	}

	void Menu::delMenu() {
		delMenuTitle();
		delMenuItems();
	}

	void Menu::delMenuItems() {
		for (int i = 0; i < total_items; i++) {
			if (menuitems[i]) {
				delete menuitems[i];
				menuitems[i] = nullptr;
			}
		}
	}

	Menu::~Menu() {
		delMenu();
	}
	Menu::Menu(const char* title, int indent) {
		if (title == nullptr) {
			emptyState();
		} else {
			indentation = indent;
			title_length = (strlen(title) + 1);
			MenuTitle = new char[title_length];
			strncpy(MenuTitle, title, title_length);
			total_items = 0;
			for (int i = 0; i < MAX_NO_OF_ITEMS; i++) {
				menuitems[i] = nullptr;
			}

		}
	}

	void Menu::emptyState() {
		MenuTitle = nullptr;
		for (int i=0; i < MAX_NO_OF_ITEMS; i++) {
			menuitems[i] = nullptr;
		}
		indentation = 0;
		title_length = 0;
		total_items = 0;
	}

	Menu::Menu(const Menu& source) {
		emptyState();
		*this = source;
		
	}
	Menu& Menu::operator=(const Menu& source) {
		if (this != &source) {
			indentation = source.indentation;
			title_length = source.title_length;

			delMenu();
			*this = source.MenuTitle;
		
		
			total_items = source.total_items;
			bool error = false;
			for (int i = 0; i < source.total_items && !error; i++) {
				if (source.menuitems[i] != nullptr) {
					if (menuitems[i] != nullptr)
						delete menuitems[i];
					menuitems[i] = new MenuItem(source.menuitems[i]->Menuitem);
				} else {
					error = true;
				}
			}
			if (error) {
				delMenu();
			}
		}
	
		return *this;
	}
	

	Menu& Menu::operator=(const char* string) {
		if (string == nullptr) {
			delMenu();
			emptyState();
		} else {
			delMenu();
			MenuTitle = new char[strlen(string)+1];
			strcpy(MenuTitle, string);
		}
		return *this;
	}
	
	
	void Menu::add(const char* item) {
		if (item == nullptr || MenuTitle == nullptr) {
			delMenu();
			emptyState();
		} else if (item!= nullptr && total_items < MAX_NO_OF_ITEMS) {
			menuitems[total_items] = new MenuItem(item);
			total_items++;
		} 
		}
	

	bool Menu::isValid() const {
		if (MenuTitle==nullptr || indentation < 0)
			return false;
		else
			return true;
	}

	Menu::operator int() const {
		return run();
	}

	Menu::operator bool() const {
		return !isEmpty();

	}

	bool Menu::isEmpty() const{
		return (MenuTitle == nullptr);

	}

	void Menu::printSpace() const {
		for(int i=0; i < indentation; i++) {
			std::cout << "    ";
		}
	}
	void Menu::display() const {
		if (!isValid()) {
			std::cout << "Invalid Menu!" << std::endl;
		} else {
			printSpace();
			std::cout << MenuTitle << std::endl;
			if (total_items == 0) {
				std::cout << "No Items to display!" << std::endl;
			} else {
				for (int i = 0; i < total_items; i++) {
					printSpace();
					std::cout << i + 1 << "- " << menuitems[i]->Menuitem << std::endl;
				}
				printSpace();
				std::cout << "> ";
			}
		}
		}
	


	Menu& Menu::operator<<(const char* string) {
		add(string);
		return *this;
	}


	int Menu::run() const {
		int selection = 0;
		display();
		if (!isEmpty() && total_items > 0)
			Utils::read(selection, 1, total_items, "Invalid selection, try again: ");
		return selection;
	
	}
			

}
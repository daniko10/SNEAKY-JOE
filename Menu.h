#ifndef MENU_H
#define MENU_H

#include "MyLibrary.h"

class Menu {
public:
	Menu(int, int, sf::Font&, std::string);

	friend void menu(sf::RenderWindow&, int*, Menu*);
	void draw(sf::RenderWindow&);
private:
	sf::Text _text;
};

void menu(sf::RenderWindow&, int *, Menu*);

#endif 

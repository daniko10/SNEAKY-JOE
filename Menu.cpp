#include "Menu.h"

int index = 0;

Menu::Menu(int x, int y, sf::Font& menu_font, std::string functional) {
	_text.setCharacterSize(40);
	_text.setStyle(sf::Text::Style::Bold);
	_text.setFillColor(sf::Color::White);
	_text.setFont(menu_font);
	_text.setPosition(sf::Vector2f(x, y));
	_text.setString(functional);
}

void Menu::draw(sf::RenderWindow& window) {
	window.draw(_text);
}

void menu(sf::RenderWindow& window, int* boolean, Menu* tab_menu) {
	int temp = index;

	for (int i = 0; i < 3; i+=2) {
		if (i == index)
			tab_menu[i]._text.setFillColor(sf::Color::Magenta);
		else
			tab_menu[i]._text.setFillColor(sf::Color::White);
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && index > 0) {
		index--;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && index < 2) {
		index++;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && index == 0)
		*boolean = 1;

	tab_menu[0].draw(window);
	tab_menu[2].draw(window);
}
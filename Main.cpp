#include "MyLibrary.h"
#include "Rectangle.h"
#include "Menu.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(1280, 720), "SNEAKY JOE");
	window.setFramerateLimit(60);
	sf::Font menu_font;
	menu_font.loadFromFile("C:\\Users\\dan-c\\Desktop\\C++\\open-sans-font\\OpenSansBoldItalic-YWD4.ttf");

	Rectangle* player = new Rectangle({ 50, 100 }, { 625, -100 }, sf::Color::Blue);
	Rectangle* levels = new Rectangle[7]{
		Rectangle({200, 50},{350, 350},sf::Color::White),
		Rectangle({200, 50},{100, 510},sf::Color::White),
		Rectangle({200, 50},{100, 190},sf::Color::White),
		Rectangle({200, 50},{550, 510},sf::Color::White),
		Rectangle({200, 50},{750, 350},sf::Color::White),
		Rectangle({200, 50},{1000, 510},sf::Color::White),
		Rectangle({200, 50},{1000, 190},sf::Color::White)
	};
	Rectangle* floor = new Rectangle({ 1280, 50 }, { 0,670 }, sf::Color::Cyan);
	
	Menu* tab_menu = new Menu[3]{
		Menu(570, 60, menu_font, "Play"),
		Menu(570, 250, menu_font, "Leave"),
		Menu(570, 160, menu_font, "Tutorial")
	};
	int boolean = 0;


	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::Closed: {
				window.close();
			} break;
			}
			if(boolean == 1){
				while (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
						player->moveD();
					}
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
						player->moveA();
					}
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
						player->jumped = true;
					}
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
						player->setSize(50, 50);
					}
					else {
						player->setSize(50, 100);
					}
					controlling(window, player, 1, floor, 1, levels, 7, &boolean, tab_menu);
				}
				player->setSize(50, 100);
			}
		}

		controlling(window, player, 1, floor, 1, levels, 7, &boolean,tab_menu);

	}

	clear_memory_single_obj(player);
	clear_memory_single_obj(floor);
	clear_memory_nonsingle_obj(levels);

}
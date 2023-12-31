#include "MyLibrary.h"
#include "Rectangle.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(1280, 720), "SNEAKY JOE");
	window.setFramerateLimit(60);

	Rectangle* player = new Rectangle({ 50, 100 }, { 615, 310 }, sf::Color::Blue);
	Rectangle* levels = new Rectangle[5]{
		Rectangle({200, 50},{100, 200},sf::Color::White),
		Rectangle({200, 50},{100, 310},sf::Color::White),
		Rectangle({200, 50},{550, 410},sf::Color::White),
		Rectangle({200, 50},{1000, 300},sf::Color::White),
		Rectangle({200, 50},{900, 550},sf::Color::White)
	};
	Rectangle* floor = new Rectangle({ 1280, 50 }, { 0,670 }, sf::Color::Cyan);

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			switch (event.type) {
				case sf::Event::Closed: {
					window.close();
				} break;
			}
			while (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
					player->moveD();
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
					player->moveA();
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
					player->jumped = true;
				}

				controlling(window, player, 1, floor, 1, levels, 5);

			}		
		}

		controlling(window, player, 1, floor, 1, levels, 5);

	}

}
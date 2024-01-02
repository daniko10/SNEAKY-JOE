#include "MyLibrary.h"
#include "Rectangle.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(1280, 720), "SNEAKY JOE");
	window.setFramerateLimit(60);

	Rectangle* player = new Rectangle({ 50, 100 }, { 625, 0 }, sf::Color::Blue);
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

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::Closed: {
				window.close();
			} break;
			}
			while (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
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
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
					player->setSize(50, 100);
				}

				controlling(window, player, 1, floor, 1, levels, 7);

			}
		}

		controlling(window, player, 1, floor, 1, levels, 7);

	}

}
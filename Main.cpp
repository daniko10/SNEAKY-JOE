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
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
				player->moveA();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
				player->moveD();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
				player->jumped = true;
			}
		}

		player->check_collision(levels, 5);
		if (player->jumped == false)
			player->gravity(levels, 5);
		else
			player->jump();

		/////////////////// PRINTING ZONE
		window.clear();

		print_rect(window, floor, 1);
		print_rect(window, levels, 5);
		print_rect(window, player, 1);

		window.display();
		/////////////////// END OF ZONE
	}

}
#include ".\\include\\MyLibrary.h"
#include ".\\include\\Menu.h"
#include ".\\include\\Rectangle.h"

int main()
{
	srand(time(nullptr));
	
	//////////////////////////// WINDOW

	sf::RenderWindow window(sf::VideoMode(1280, 720), "SNEAKY JOE");
	window.setFramerateLimit(60);

	//////////////////////////// FONTS

	sf::Font menu_font;
	menu_font.loadFromFile(".\\assets\\open-sans-font\\OpenSansBoldItalic-YWD4.ttf");

	//////////////////////////// TEXTURES
	
	sf::Texture player_stand;
	if (player_stand.loadFromFile(".\\assets\\images\\character.png")) std::cout << "Pregame: Texture loaded!\n";
	sf::Texture player_left;
	if(player_left.loadFromFile(".\\assets\\images\\character_left_side.png")) std::cout << "Pregame: Texture loaded!\n";
	sf::Texture player_right;
	if(player_right.loadFromFile(".\\assets\\images\\character_right_side.png")) std::cout << "Pregame: Texture loaded!\n";
	sf::Texture level;
	if(level.loadFromFile(".\\assets\\images\\level.png")) std::cout << "Pregame: Texture loaded!\n";
	sf::Texture floor_level;
	if(floor_level.loadFromFile(".\\assets\\images\\floor.png")) std::cout << "Pregame: Texture loaded!\n";
	sf::Texture background;
	if(background.loadFromFile(".\\assets\\images\\background.jpg")) std::cout << "Pregame: Texture loaded!\n";
	sf::Texture heart_image;
	if(heart_image.loadFromFile(".\\assets\\images\\heart.png")) std::cout << "Pregame: Texture loaded!\n";
	sf::Texture rocket_right;
	if(rocket_right.loadFromFile(".\\assets\\images\\rocket_to_right.png")) std::cout << "Pregame: Texture loaded!\n";
	sf::Texture rocket_left;
	if(rocket_left.loadFromFile(".\\assets\\images\\rocket_to_left.png")) std::cout << "Pregame: Texture loaded!\n";
	sf::Texture vodka_image;
	if(vodka_image.loadFromFile(".\\assets\\images\\vodka.png")) std::cout << "Pregame: Texture loaded!\n";
	sf::Font font;
	if(font.loadFromFile(".\\assets\\open-sans-font\\OpenSansItalic-KwXl.ttf")) std::cout << "Pregame: Font loaded!\n";

	//////////////////////////// OBJECTS

	int life_left = 4;
	int vodka_bonus = 0;
	int boolean = 0;
	bool closed = false;

	Rectangle* player = new Rectangle({ 50, 100 }, { 625, -100 }, sf::Color::Blue, &player_stand);

	Rectangle* levels = new Rectangle[7]{
		Rectangle({200, 50},{350, 350},sf::Color::White,&level),
		Rectangle({200, 50},{100, 510},sf::Color::White,&level),
		Rectangle({200, 50},{100, 190},sf::Color::White,&level),
		Rectangle({200, 50},{550, 510},sf::Color::White,&level),
		Rectangle({200, 50},{750, 350},sf::Color::White,&level),
		Rectangle({200, 50},{1000, 510},sf::Color::White,&level),
		Rectangle({200, 50},{1000, 190},sf::Color::White,&level)
		
	};
	
	Rectangle* floor = new Rectangle({ 1280, 50 }, { 0,670 }, sf::Color::Cyan, &floor_level);
	
	Rectangle* background_p = new Rectangle({ 1280, 720 }, { 0,0 }, sf::Color::Blue, &background);

	Menu* tab_menu = new Menu[3]{
		Menu(570, 60, menu_font, "Play"),
		Menu(570, 160, menu_font, "Tutorial"),
		Menu(570, 260, menu_font, "Leave")
	};

	Rectangle* life = new Rectangle[4]{
		Rectangle({50,50},{250, 20}, sf::Color::Blue,&heart_image),
		Rectangle({50,50},{320, 20}, sf::Color::Blue,&heart_image),
		Rectangle({50,50},{390, 20}, sf::Color::Blue,&heart_image),
		Rectangle({50,50},{460, 20}, sf::Color::Blue,&heart_image)
	};

	Rectangle* rockets = new Rectangle[4]{
		Rectangle({100, 50}, {-100, 100}, sf::Color::Blue,&rocket_right, true),
		Rectangle({100, 50}, {-100, 340}, sf::Color::Blue,&rocket_right, true),
		Rectangle({100, 50}, {1280, 200}, sf::Color::Blue,&rocket_left, false),
		Rectangle({100, 50}, {1280, 400}, sf::Color::Blue,&rocket_left, false)
	};

	Rectangle* bonus_heart = new Rectangle({ 50,50 }, { 825, 290 }, sf::Color::Blue, &heart_image);
	Rectangle* bonus_vodka = new Rectangle({ 30,60 }, { 175, 130 }, sf::Color::Blue, &vodka_image);
	Rectangle* i_vodka = new Rectangle({ 20,40 }, { 550, 20 }, sf::Color::Blue, &vodka_image);

	sf::Text text;
	text.setCharacterSize(30);
	text.setFillColor(sf::Color::Black);
	text.setStyle(sf::Text::Style::Bold);
	text.setPosition(580, 25);
	text.setString(": 0");
	text.setFont(font);

	//////////////////////////// MAIN LOOP

	while (window.isOpen()) {

		if (life_left == 0 || boolean == 3) {
			std::cout << "Output: Game ended! Thanks!";

			clear_memory_single_obj(player);
			clear_memory_single_obj(floor);
			clear_memory_single_obj(background_p);
			clear_memory_single_obj(bonus_heart);
			clear_memory_single_obj(i_vodka);
			clear_memory_single_obj(bonus_vodka);
			clear_memory_nonsingle_obj(life);
			clear_memory_nonsingle_obj(levels);
			clear_memory_nonsingle_obj(rockets);

			exit(0);
		}
		else if (boolean == 2) {
			tutorial(window, &player_stand, &player_left, &player_right, &level, &background, &boolean, font);
		}
		sf::Event event;
		while (window.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::Closed: {
				window.close();
			} break;
			}
			if(boolean == 1 && life_left != 0){
				while (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
						player->moveD();
						player->setTexture(&player_right);
					}
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
						player->moveA();
						player->setTexture(&player_left);
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
					if(!sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !sf::Keyboard::isKeyPressed(sf::Keyboard::A) && sf::Keyboard::isKeyPressed(sf::Keyboard::S))
						player->setTexture(&player_stand);
					controlling(window, player, 1, floor, 1, levels, 7, &boolean, tab_menu, background_p, life, &life_left, rockets, 4, bonus_heart, bonus_vodka,&vodka_bonus, i_vodka, text);
				}
				player->setTexture(&player_stand);
				player->setSize(50, 100);
			}
		}
		
		controlling(window, player, 1, floor, 1, levels, 7, &boolean,tab_menu, background_p, life, &life_left, rockets, 4, bonus_heart, bonus_vodka, &vodka_bonus, i_vodka, text);

	}

}
#include "MyLibrary.h"
#include "Rectangle.h"
#include "Menu.h"

float gravity_down_jump = 0.0;
float gravity_down = 0.0;
bool level_above = false;
bool first_touch = false;
bool invisible = true;

///////////////////////////////////////////// METHODS

Rectangle::Rectangle(sf::Vector2f size, sf::Vector2f position, sf::Color color, sf::Texture* texture) {
	_rect.setPosition(position);
	_rect.setSize(size);
	if(color != sf::Color::Blue)
		_rect.setFillColor(color);
	_rect.setTexture(texture);

	_width = position.x;
	_height = position.y;
	_size_y = size.y;
	_size_x = size.x;
}

Rectangle::Rectangle(sf::Vector2f size, sf::Vector2f position, sf::Color color, sf::Texture* texture, bool s) {
	std::cout << "Output: New Rectangle object created!\n";
	_rect.setPosition(position);
	_rect.setSize(size);
	if (color != sf::Color::Blue)
		_rect.setFillColor(color);
	_rect.setTexture(texture);

	_width = position.x;
	_height = position.y;
	_size_y = size.y;
	_size_x = size.x;
	rocket_to_right = s;
}

void Rectangle::draw(sf::RenderWindow& window) {
	window.draw(_rect);
}

void Rectangle::move_rocket(Rectangle* rockets, int size, int *heart, Rectangle* player) {
	bool hitted = false;
	player->control_rocket(rockets, size, heart);
	
	if(invisible)
		for (int i = 0; i < size;i++) {
			if (rockets[i]._width > player->_width) {
				if (rockets[i]._height < player->_height) {
					if (rockets[i]._width <= player->_width + player->_size_x && player->_height - rockets[i]._height < rockets[i]._size_y) {
						hitted = true;
						break;
					}
				}
				else {
					if (rockets[i]._width <= player->_width + player->_size_x && rockets[i]._height - player->_height < player->_size_y) {
						hitted = true;
						break;
					}
				}
			}
			else {
				if (rockets[i]._height < player->_height) {
					if (rockets[i]._width + rockets[i]._size_x >= player->_width && player->_height - rockets[i]._height < rockets[i]._size_y) {
						hitted = true;
						break;
					}
				}
				else {
					if (rockets[i]._width + rockets[i]._size_x >= player->_width && rockets[i]._height - player->_height < player->_size_y) {
						hitted = true;
						break;
					}
				}
			}
		}

	if (hitted) {
		(*heart) -= 1;
		std::cout << "Output: Player is hitted by the rocket! Life remained: " << *heart << std::endl;
		invisible = false;
		player->_height = -100;
		player->_width = 625;
		if (*heart == 0) {
			exit(0);
		}
	}

	if (rocket_to_right && _width < 1280)
		_width += 8;
	else if (!rocket_to_right && _width > -100)
		_width -= 8;

	_rect.setPosition(_width, _height);
}

void Rectangle::moveA() {
	if (!first_touch)
		return;

	max_width_left = max_width_left == true ? true : _width > 0 ? false : true;
	_width = max_width_left == false ? _width -= 2 : _width;

	_rect.setPosition(_width, _height);
}

void Rectangle::moveD() {
	if (!first_touch)
		return;

	max_width_right = max_width_right == true ? true : _width < 1230 ? false : true;
	_width = max_width_right == false ? _width += 2 : _width;

	_rect.setPosition(_width, _height);
}

void Rectangle::moveA(int a, int b) {
	
	max_width_left = max_width_left == true ? true : _width > a ? false : true;
	_width = max_width_left == false ? _width -= 2 : b;

	if (max_width_left == true)
		max_width_left = false;

	_rect.setPosition(_width, _height);
}

void Rectangle::moveD(int a, int b) {
	
	max_width_right = max_width_right == true ? true : _width < b ? false : true;
	_width = max_width_right == false ? _width += 2 : a;

	if (max_width_right == true)
		max_width_right = false;

	_rect.setPosition(_width, _height);
}

void Rectangle::jump() {

	if (!can_jump || level_above)
	{
		jumped = false;
		return;
	}

	jumped = true;

	_height = can_jump == true ? _height > _position_jump - 200 ? _height - 10 + gravity_down_jump : _height : _height;
	gravity_down_jump = can_jump == true ? gravity_down_jump += 0.2 : 0;

	if (_height <= _position_jump - 200) {
		jumped = false;
		can_jump = false;
	}

	_rect.setPosition(_width, _height);

}

int check_vodka(Rectangle* bonus_vodka, Rectangle* player) {
	bool hitted = false;

	if (bonus_vodka->_width > player->_width) {
		if (bonus_vodka->_height < player->_height) {
			if (bonus_vodka->_width <= player->_width + player->_size_x && player->_height - bonus_vodka->_height < bonus_vodka->_size_y) {
				hitted = true;
			}
		}
		else {
			if (bonus_vodka->_width <= player->_width + player->_size_x && bonus_vodka->_height - player->_height < player->_size_y) {
				hitted = true;
			}
		}
	}
	else {
		if (bonus_vodka->_height < player->_height) {
			if (bonus_vodka->_width + bonus_vodka->_size_x >= player->_width && player->_height - bonus_vodka->_height < bonus_vodka->_size_y) {
				hitted = true;
			}
		}
		else {
			if (bonus_vodka->_width + bonus_vodka->_size_x >= player->_width && bonus_vodka->_height - player->_height < player->_size_y) {
				hitted = true;
			}
		}
	}

	if (hitted) {
		std::cout << "Output: Bonus taken\n";
		int choice;
		int width = 0, height = 0;

		do {
			choice = rand() % 7;
			if (choice == 0) {
				width = 425;
				height = 300;
			}
			else if (choice == 1) {
				width = 175;
				height = 460;
			}
			else if (choice == 2) {
				width = 175;
				height = 140;
			}
			else if (choice == 3) {
				width = 625;
				height = 460;
			}
			else if (choice == 4) {
				width = 825;
				height = 300;
			}
			else if (choice == 5) {
				width = 1075;
				height = 460;
			}
			else if (choice == 6) {
				width = 1075;
				height = 140;
			}
		} while (bonus_vodka->_width == width && bonus_vodka->_height == height);
		bonus_vodka->_width = width;
		bonus_vodka->_height = height;
		bonus_vodka->_rect.setPosition(width, height);
		return 1;
	}
	else
		return 0;
}

void controlling(sf::RenderWindow& window, Rectangle* player, int size_player, Rectangle* floor, int size_floor, Rectangle* levels, int size_levels, int* boolean, Menu* tab_menu, Rectangle* background, Rectangle* hearts, int* size_heart, Rectangle* rockets, int size_rockets, Rectangle* bonus_heart, Rectangle* bonus_vodka, int* vodka_count, Rectangle* i_vodka, sf::Text t) {

	print_rect(window, background, 1);

	if (*size_heart == 0) {
		*boolean = 3;
		return;
	}

	if (*boolean == 0) {
		menu(window, boolean, tab_menu);
	}
	else {
		for (int i = 0; i < size_levels; i++) {
			if (((player->_height - levels[i]._height < 50 && player->_height > levels[i]._height) && (player->_width > levels[i]._width - 50 && player->_width < levels[i]._width + 200)) || player->_height <= 0) {
				level_above = true;
				break;
			}
		}

		player->check_collision(levels, size_levels);
		if (player->jumped == false || player->can_jump == false || level_above)
			player->gravity(levels, size_levels, *boolean);
		else {
			player->jump();
		}
	}
	t.setString(": " + std::to_string(*vodka_count));

	window.draw(t);
	print_rect(window, i_vodka, 1);
	print_rect(window, bonus_vodka, 1);
	print_rect(window, bonus_heart, 1);
	print_rect(window, hearts, *size_heart);
	print_rect(window, floor, size_floor);
	print_rect(window, levels, size_levels);
	print_rect(window, player, size_player);

	if (*boolean != 0) {
		print_rect(window, rockets, size_rockets);
		for (int i = 0; i < size_rockets; i++)
			rockets[i].move_rocket(rockets, size_rockets, size_heart, player);
	}

	if (check_bonus(bonus_heart, player)) {
		std::cout << "Output: Player collected additional health!\n";
		if (*size_heart < 4)
			(*size_heart)++;
	}

	if (check_vodka(bonus_vodka, player)) {
		(*vodka_count)++;
	}

	window.display();

	level_above = false;
}

int check_bonus(Rectangle* bonus_heart, Rectangle* player) {
	bool hitted = false;
	if (bonus_heart->_width > player->_width) {
		if (bonus_heart->_height < player->_height) {
			if (bonus_heart->_width <= player->_width + player->_size_x && player->_height - bonus_heart->_height < bonus_heart->_size_y) {
				hitted = true;
				
			}
		}
		else {
			if (bonus_heart->_width <= player->_width + player->_size_x && bonus_heart->_height - player->_height < player->_size_y) {
				hitted = true;
				
			}
		}
	}
	else {
		if (bonus_heart->_height < player->_height) {
			if (bonus_heart->_width + bonus_heart->_size_x >= player->_width && player->_height - bonus_heart->_height < bonus_heart->_size_y) {
				hitted = true;
				
			}
		}
		else {
			if (bonus_heart->_width + bonus_heart->_size_x >= player->_width && bonus_heart->_height - player->_height < player->_size_y) {
				hitted = true;
			
			}
		}
	}

	if (hitted) {
		int choice;
		int width = 0, height = 0;

		do {
			choice = rand() % 7;
			if (choice == 0) {
				width = 425;
				height = 300;
			}
			else if (choice == 1) {
				width = 175;
				height = 460;
			}
			else if (choice == 2) {
				width = 175;
				height = 140;
			}
			else if (choice == 3) {
				width = 625;
				height = 460;
			}
			else if (choice == 4) {
				width = 825;
				height = 300;
			}
			else if (choice == 5) {
				width = 1075;
				height = 460;
			}
			else if (choice == 6) {
				width = 1075;
				height = 140;
			}
		} while (bonus_heart->_width == width && bonus_heart->_height == height);
		bonus_heart->_width = width;
		bonus_heart->_height = height;
		bonus_heart->_rect.setPosition(width, height);
		return 1;
	}
	else
		return 0;
}

void Rectangle::check_collision(Rectangle* levels, int size) {
	for (int i = 0; i < size; i++) {
		if ((_width > levels[i]._width - _size_x + 3 && _width < levels[i]._width + levels[i]._size_x - 3) && (_height >= levels[i]._height - _size_y && _height <= levels[i]._height + levels[i]._size_y))
			return;
		if (levels[i]._width > _width) {
			if (levels[i]._height < _height) {
				if ((_height - levels[i]._height < levels[i]._size_y) && (levels[i]._width - _width < _size_x))
				{
					max_width_right = true;
					_width = levels[i]._width - _size_x;
				}
				else
					max_width_right = false;
			}
			else {
				if ((levels[i]._height - _height < _size_y) && (levels[i]._width - _width < _size_x))
				{
					max_width_right = true;
					_width = levels[i]._width - _size_x;
				}
				else
					max_width_right = false;
			}
		}
		else if (levels[i]._width < _width) {
			if (levels[i]._height < _height) {
				if ((levels[i]._height - _height > -levels[i]._size_y) && (levels[i]._width - _width > -levels[i]._size_x))
				{
					max_width_left = true;
					_width = levels[i]._width + levels[i]._size_x;
				}
				else
					max_width_left = false;
			}
			else {
				if ((levels[i]._height - _height < _size_y) && (levels[i]._width - _width > -levels[i]._size_x))
				{
					max_width_left = true;
					_width = levels[i]._width + levels[i]._size_x;
				}
				else
					max_width_left = false;
			}
		}
	}

	_rect.setPosition(_width, _height);
}

void Rectangle::gravity(Rectangle* levels, int size, int boolean) {
	if (boolean == 0)
		return;
	bool standing = false;

	for (int i = 0; i < size;i++) {
		if ((_height <= levels[i]._height && _height >= levels[i]._height - _size_y) && ((_width - levels[i]._width > -50 && _width < levels[i]._width + 200) || (_width - levels[i]._width < 0 && _width > levels[i]._width - 50)))
		{
			invisible = true;
			_height = levels[i]._height - _size_y;
			_rect.setPosition(_width, _height);
			_position_jump = levels[i]._height - _size_y;
			standing = true;
			break;
		}
	}

	if (_height == 570 && _size_y == 100) {
		_position_jump = 570;
		standing = true;
	}
	else if (_height == 620 && _size_y == 50) {
		_position_jump = 620;
		standing = true;
	}

	if (standing) {
		first_touch = true;
		can_jump = true;
		gravity_down = 0;
		gravity_down_jump = 0;
		return;
	}

	can_jump = false;
	jumped = false;
	if (_size_y == 100)
		_height = _height < 570 ? _height += 5 + gravity_down : _height = 570;
	else if (_size_y == 50)
		_height = _height < 620 ? _height += 3 + gravity_down : _height = 620;
	_rect.setPosition(_width, _height);

	gravity_down += 0.2;
}

void Rectangle::setSize(int x, int y) {
	hide = y == 50 ? true : hide;
	_rect.setSize(sf::Vector2f(x, y));
	_size_y = y;

	if (y == 100 && hide) {
		_height -= 50;
		_rect.setPosition(_width, _height);
		hide = false;
	}
}

void Rectangle::setTexture(sf::Texture* texture) {
	_rect.setTexture(texture);
}

void Rectangle::control_rocket(Rectangle* rockets, int size, int* nmbr_heart) {

	if (*nmbr_heart == 0)
		return;

	int rand_nmbr = rand() % 671;

	for (int i = 0; i < size; i++) {
		if (rockets[i].rocket_to_right && rockets[i]._width >= 1280) {
			rockets[i]._width = -100 - rand() % 100;
			for (int j = 0; j < size;j++) {
				if (rockets[j]._height > rand_nmbr + 50 || rockets[j]._height < rand_nmbr - 50);
				else {
					j = 0;
					rand_nmbr = rand() % 671;
				}
			}
			rockets[i]._height = rand_nmbr;
		}
		else if (!(rockets[i].rocket_to_right) && rockets[i]._width <= -100) {
			rockets[i]._width = 1280 + rand() % 100;
			for (int j = 0; j < size;j++) {
				if (rockets[j]._height > rand_nmbr + 50 || rockets[j]._height < rand_nmbr - 50);
				else {
					j = 0;
					rand_nmbr = rand() % 671;
				}
			}
			rockets[i]._height = rand_nmbr;
		}
	}

}

///////////////////////////////////////////// METHODS

void tutorial(sf::RenderWindow& window,sf::Texture* texture_player_stand, sf::Texture* texture_player_left, sf::Texture* texture_player_right, sf::Texture* texture_level, sf::Texture* texture_background, int* boolean, sf::Font font) {
	Rectangle* tutorial_levels = new Rectangle[4]{
		Rectangle({200,50},{900,400},sf::Color::Blue, texture_level),
		Rectangle({200,50},{650,400},sf::Color::Blue, texture_level),
		Rectangle({200,50},{400,400},sf::Color::Blue, texture_level),
		Rectangle({200,50},{150,400},sf::Color::Blue, texture_level)
	};
	Rectangle* tutorial_players = new Rectangle[4]{
		Rectangle({50,50},{975, 350},sf::Color::Blue, texture_player_stand),
		Rectangle({50,100},{725,300}, sf::Color::Blue, texture_player_right),
		Rectangle({50,100},{475, 300}, sf::Color::Blue, texture_player_left),
		Rectangle({50,100},{225, 300},sf::Color::Blue, texture_player_stand)
	};
	Rectangle* background = new Rectangle({ 1280, 720 }, { 0,0 }, sf::Color::Blue, texture_background);

	int counter = 0;

	sf::Text text1, text2, text3, text4, leave;
	
	leave.setString("Press ESC to leave the tutorial!");
	leave.setPosition({ 400,100 });
	leave.setFont(font);
	leave.setFillColor(sf::Color::Blue);
	leave.setStyle(sf::Text::Style::Bold);
	leave.setCharacterSize(35);

	text1.setString("Space");
	text1.setPosition({ 218,470 });
	text1.setFont(font);
	text1.setFillColor(sf::Color::Black);

	text2.setString("A");
	text2.setPosition({ 475,470 });
	text2.setFont(font);
	text2.setFillColor(sf::Color::Black);

	text3.setString("D");
	text3.setPosition({ 725, 470 });
	text3.setFont(font);
	text3.setFillColor(sf::Color::Black);

	text4.setString("S");
	text4.setPosition({ 975, 470 });
	text4.setFont(font);
	text4.setFillColor(sf::Color::Black);

	while (true) {
		window.clear();
		background->draw(window);
		window.draw(leave);
		window.draw(text1);
		window.draw(text2);
		window.draw(text3);
		window.draw(text4);
		print_rect(window, tutorial_players, 4);
		print_rect(window, tutorial_levels, 4);
		
		tutorial_players[2].moveA(400, 550);
		tutorial_players[1].moveD(650, 800);
		tutorial_players[3].jump();
		if(!(tutorial_players[3].jumped))
			tutorial_players[3].gravity(tutorial_levels + 3, 1, 1);
		if (counter%50 == 0)
		{
			tutorial_players[0].setSize(50, 100);	
			tutorial_players[0]._rect.setPosition({ 975, 300 });
		}
		if(counter%100 == 0){
			tutorial_players[0].setSize(50, 50);
			tutorial_players[0]._rect.setPosition({975, 350});
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
			*boolean = 0;
			break;
		}

		window.display();
		counter++;
	}
}

void print_rect(sf::RenderWindow& window, Rectangle* ptr, int size) {
	for (int i = 0; i < size;i++)
		ptr[i].draw(window);
}

void clear_memory_single_obj(Rectangle* ptr) {
	delete ptr;
}

void clear_memory_nonsingle_obj(Rectangle* ptr) {
	delete[] ptr;
}

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
	}

	if(rocket_to_right && _width < 1280)
		_width += 8;
	else if(!rocket_to_right && _width > -100)
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

void Rectangle::jump() {

	if (!can_jump || level_above)
	{
		jumped = false;
		return;
	}

	_height = can_jump == true ? _height > _position_jump - 200 ? _height - 10 + gravity_down_jump : _height : _height;
	gravity_down_jump = can_jump == true ? gravity_down_jump += 0.2 : 0;

	if (_height <= _position_jump - 200) {
		jumped = false;
		can_jump = false;
	}

	_rect.setPosition(_width, _height);

}

void controlling(sf::RenderWindow& window, Rectangle* player, int size_player, Rectangle* floor, int size_floor, Rectangle* levels, int size_levels, int* boolean, Menu* tab_menu, Rectangle* background, Rectangle* hearts, int* size_heart, Rectangle* rockets, int size_rockets) {
	window.clear();
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

	print_rect(window, hearts, *size_heart);
	print_rect(window, floor, size_floor);
	print_rect(window, levels, size_levels);
	print_rect(window, player, size_player);

	if (*boolean != 0) {
		print_rect(window, rockets, size_rockets);
		for (int i = 0; i < size_rockets; i++)
			rockets[i].move_rocket(rockets, size_rockets, size_heart, player);
	}

	window.display();

	level_above = false;
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
	bool create_new = false;

	for (int i = 0; i < size; i++) {
		if (rockets[i].rocket_to_right && rockets[i]._width >= 1280) {
			create_new = true;
			rockets[i]._width = -100;
		}
		else if (!(rockets[i].rocket_to_right) && rockets[i]._width <= -100) {
			create_new = true;
			rockets[i]._width = 1280;
		}
	}

	if (create_new) {
		int first = rand() % 360;
		rockets[0]._height = first;
		first = rand() % 360;
		rockets[size / 2]._height = first;
		for (int i = 1; i < size / 2; i++)
			rockets[i]._height = rockets[i - 1]._height + 50 + rand() % 300;
		for (int i = size / 2 + 1; i < size;i++)
			rockets[i]._height = rockets[i - 1]._height + 50 + rand() % 300;
	}

}

///////////////////////////////////////////// METHODS

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

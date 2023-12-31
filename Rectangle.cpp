#include "MyLibrary.h"
#include "Rectangle.h"

///////////////////////////////////////////// METHODS

Rectangle::Rectangle(sf::Vector2f size, sf::Vector2f position, sf::Color color) {
	_rect.setPosition(position);
	_rect.setSize(size);
	_rect.setFillColor(color);

	_width = position.x;
	_height = position.y;
}

void Rectangle::draw(sf::RenderWindow& window) {
	window.draw(_rect);
}

void Rectangle::moveA() {
	
	max_width_left = max_width_left == true ? true : _width > 0 ? false : true;
	_width = max_width_left == false ? _width -= 2 : _width;

	_rect.setPosition(_width, _height);
}

void Rectangle::moveD() {

	max_width_right = max_width_right == true ? true : _width < 1230 ? false : true;
	_width = max_width_right == false ? _width += 2 : _width;

	_rect.setPosition(_width, _height);
}

void Rectangle::jump(sf::RenderWindow& window) {

	if (!can_jump)
	{
		jumped = false;
		return;
	}

	_height = can_jump == true ? _height > _position_jump - 150 ? _height -= 5 : _height : _height;

	if ( _height <= _position_jump - 150 ) {
		jumped = false;
		can_jump = false;
	}

	_rect.setPosition(_width, _height);

}

void controlling(sf::RenderWindow& window, Rectangle* player, int size_player, Rectangle* floor, int size_floor, Rectangle* levels, int size_levels) {

	player->check_collision(levels, size_levels);
	if (player->jumped == false || player->can_jump == false)
		player->gravity(levels, size_levels);
	else
		player->jump(window);

	window.clear();

	print_rect(window, floor, size_floor);
	print_rect(window, levels, size_levels);
	print_rect(window, player, size_player);

	window.display();
}

void Rectangle::check_collision(Rectangle* levels, int size) {
	for (int i = 0; i < size; i++) {
		if (levels[i]._width > _width) {
			if (levels[i]._height < _height) {
				if ((levels[i]._height - _height < 50 && levels[i]._height - _height > -50) && (levels[i]._width - _width < 50 && levels[i]._width - _width > -50))
					max_width_right = true;
				else
					max_width_right = false;
			}
			else {
				if ((levels[i]._height - _height < 100 && levels[i]._height - _height > -100) && (levels[i]._width - _width < 50 && levels[i]._width - _width > -50))
					max_width_right = true;
				else
					max_width_right = false;
			}
		}
		else {
			if (levels[i]._height < _height) {
				if ((levels[i]._height - _height < 50 && levels[i]._height - _height > -50) && (levels[i]._width - _width < 200 && levels[i]._width - _width > -200))
					max_width_left = true;
				else
					max_width_left = false;
			}
			else {
				if ((levels[i]._height - _height < 100 && levels[i]._height - _height > -100) && (levels[i]._width - _width < 200 && levels[i]._width - _width > -200))
					max_width_left = true;
				else
					max_width_left = false;
			}
		}
	}
	
}

void Rectangle::gravity(Rectangle* levels, int size) {
	bool standing = false;
	
	for (int i = 0; i < size;i++) {
		if (( _height < levels[i]._height - 95 && _height >= levels[i]._height - 100) && ((_width - levels[i]._width >= 0 && _width <= levels[i]._width + 200) || (_width - levels[i]._width <0 && _width > levels[i]._width - 50)))
	 	{
			_height = levels[i]._height - 100;
			_rect.setPosition(_width, _height);
			_position_jump = levels[i]._height - 100;
			standing = true;
			break;
		}
	}

	if (_height == 570) {
		_position_jump = 570;
		standing = true;
	}

	if (standing) {
		can_jump = true;
		return;
	}
	
	can_jump = false;

	_height = _height < 570 ? _height += 3 : _height = 570;
	_rect.setPosition(_width, _height);

}

///////////////////////////////////////////// METHODS

void print_rect(sf::RenderWindow& window, Rectangle* ptr, int size) {
	for (int i = 0; i < size;i++)
		ptr[i].draw(window);
}
#include "MyLibrary.h"
#include "Rectangle.h"

static float gravity_down = 0.0;
bool level_above = false;

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

void Rectangle::jump() {

	if (!can_jump || level_above)
	{
		jumped = false;
		return;
	}

	_height = can_jump == true ? _height > _position_jump - 200 ? _height -= 5 : _height : _height;

	if ( _height <= _position_jump - 200 ) {
		jumped = false;
		can_jump = false;
	}

	_rect.setPosition(_width, _height);

}

void controlling(sf::RenderWindow& window, Rectangle* player, int size_player, Rectangle* floor, int size_floor, Rectangle* levels, int size_levels) {
	
	for (int i = 0; i < size_levels; i++) {
		if ((player->_height - levels[i]._height < 50 && player->_height > levels[i]._height) && (player->_width > levels[i]._width - 50 && player->_width < levels[i]._width + 200)) {
			level_above = true;
			break;
		}
	}

	player->check_collision(levels, size_levels);
	if (player->jumped == false || player->can_jump == false || level_above)
		player->gravity(levels, size_levels);
	else
		player->jump();

	window.clear();

	print_rect(window, floor, size_floor);
	print_rect(window, levels, size_levels);
	print_rect(window, player, size_player);

	window.display();

	level_above = false;
}

void Rectangle::check_collision(Rectangle* levels, int size) {
	for (int i = 0; i < size; i++) {
		if ((_width > levels[i]._width - 47 && _width < levels[i]._width + 197) && (_height >= levels[i]._height - 100 && _height <= levels[i]._height + 50))
			return;
		if (levels[i]._width > _width ) {
			if (levels[i]._height < _height) {
				if ((_height - levels[i]._height < 50) && (levels[i]._width - _width < 50))
				{
					max_width_right = true;
					_width = levels[i]._width - 50;
				}
				else
					max_width_right = false;
			}
			else {
				if ((levels[i]._height - _height < 100) && (levels[i]._width - _width < 50 ))
				{
					max_width_right = true;
					_width = levels[i]._width - 50;
				}
				else
					max_width_right = false;
			}
		}
		else if(levels[i]._width  < _width) {
			if (levels[i]._height < _height) {
				if ((levels[i]._height - _height > -50) && (levels[i]._width - _width > -200))
				{
					max_width_left = true;
					_width = levels[i]._width + 200;
				}
				else
					max_width_left = false;
			}
			else {
				if ((levels[i]._height - _height < 100) && (levels[i]._width - _width > -200))
				{
					max_width_left = true;
					_width = levels[i]._width + 200;
				}
				else
					max_width_left = false;
			}
		}
	}
	
	_rect.setPosition(_width, _height);
}

void Rectangle::gravity(Rectangle* levels, int size) {
	bool standing = false;
	
	for (int i = 0; i < size;i++) {
		if (( _height <= levels[i]._height && _height >= levels[i]._height - 100) && ((_width - levels[i]._width > -50 && _width < levels[i]._width + 200) || (_width - levels[i]._width < 0 && _width > levels[i]._width - 50)))
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
		gravity_down = 0;
		return;
	}
	
	can_jump = false;
	jumped = false;
	_height = _height < 570 ? _height += 3 + gravity_down : _height = 570;
	_rect.setPosition(_width, _height);

	gravity_down += 0.2;
}

///////////////////////////////////////////// METHODS

void print_rect(sf::RenderWindow& window, Rectangle* ptr, int size) {
	for (int i = 0; i < size;i++)
		ptr[i].draw(window);
}
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

void Rectangle::jump() {

	if (!can_jump)
	{
		jumped = false;
		return;
	}

	_height = can_jump == true ? _height > _position_jump - 150 ? _height -= 2 : _height : _height;

	if ( _height <= _position_jump - 150 ) {
		jumped = false;
		can_jump = false;
	}

	_rect.setPosition(_width, _height);

}

void Rectangle::check_collision(Rectangle* levels, int size) {
	for (int i = 0; i < size; i++) {
		if (levels[i]._width > _width) {
			if (levels[i]._height > _height) {
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
			if (levels[i]._height > _height) {
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
		if (levels[i]._height - 100 == _height && ((_width - levels[i]._width >= 0 && _width <= levels[i]._width + 200) || (_width - levels[i]._width <0 && _width > levels[i]._width - 50)))
		{
			_position_jump = levels[i]._height - 100;
			standing = true;
			break;
		}
	}

	if (_height == 570) {
		_position_jump = 470;
		standing = true;
	}

	if (standing) {
		can_jump = true;
		return;
	}
	else
		can_jump = false;

	_height = _height < 570 ? _height += 2 : _height = 570;
	_rect.setPosition(_width, _height);

}

///////////////////////////////////////////// METHODS

void print_rect(sf::RenderWindow& window, Rectangle* ptr, int size) {
	for (int i = 0; i < size;i++)
		ptr[i].draw(window);
}
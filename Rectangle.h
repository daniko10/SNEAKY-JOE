#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "MyLibrary.h"

class Rectangle {
public:
	Rectangle() = default;
	Rectangle(sf::Vector2f, sf::Vector2f, sf::Color);
	void draw(sf::RenderWindow&);
	void moveA();
	void moveD();
	void jump();
	void gravity(Rectangle*, int);
	void check_collision(Rectangle*, int);

	bool jumped = false;
	friend void print_rect(sf::RenderWindow&, Rectangle*, int);
private:
	sf::RectangleShape _rect;
	bool max_width_left = false;
	bool max_width_right = false;
	bool max_height = false;
	bool can_jump = false;
	int _width;
	int _height;
	int _position_jump = 310;
};

#endif

#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "MyLibrary.h"
#include "Menu.h"

class Rectangle {
public:
	Rectangle() = default;
	Rectangle(sf::Vector2f, sf::Vector2f, sf::Color, sf::Texture*);
	Rectangle(sf::Vector2f, sf::Vector2f, sf::Color, sf::Texture*, bool);
	void draw(sf::RenderWindow&);
	void move_rocket(Rectangle*, int, int*, Rectangle*);
	void moveA();
	void moveD();
	void jump();
	void gravity(Rectangle*, int, int);
	void check_collision(Rectangle*, int);
	void setSize(int, int);
	void setTexture(sf::Texture*);
	void control_rocket(Rectangle*, int, int*);

	bool jumped = false;
	friend void print_rect(sf::RenderWindow&, Rectangle*, int);
	friend void controlling(sf::RenderWindow&, Rectangle*, int, Rectangle*, int, Rectangle*, int, int*, Menu*, Rectangle*, Rectangle*, int*, Rectangle*, int, Rectangle*);
	friend int check_bonus(Rectangle*, Rectangle*);
	friend void clear_memory_single_obj(Rectangle*);
	friend void clear_memory_nonsingle_obj(Rectangle*);
private:
	sf::RectangleShape _rect;
	bool max_width_left = false;
	bool max_width_right = false;
	bool max_height = false;
	bool can_jump = false;
	bool hide = false;
	bool rocket_to_right = false;
	int _width;
	int _height;
	int _position_jump = 310;
	int _size_y;
	int _size_x;
};

#endif

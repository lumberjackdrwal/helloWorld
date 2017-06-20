#pragma once
#include "Figury.h"

enum Color
{
	WHITE,
	BLACK
};

class Field;

class Player
{
	int score;
	Color color;
public:
	Player(Color color);
	Player();
	~Player();
	//getters and setters
	Color getColor();
	std::string getColorName();
	void setColor(Color new_color);
	void addScore(int points);
	int getScore();
	//methods
	Field *getMove();
	void move();
};

bool operator==(Player &that, Player &other);
bool operator!=(Player &that, Player &other);
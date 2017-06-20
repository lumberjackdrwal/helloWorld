#pragma once
#include <iostream>
#include "Player.h"
#include "Field.h"
using std::string;

//Wspolrzedne na szachownicy numerowane od 1 do 8 od lewego dolnego rogu

class Field;
class Player;

class Piece //klasa figury szachowej
{
protected:
	string name;
	int value;
	Player *player;
	char symbol;
public:
	Field *field;
	//constructor and destructor
	Piece(Field *field, Player *player);
	virtual ~Piece() = 0;
	//getters
	string getName();
	Field *getField();
	int get_value();
	Player *getPlayer();
	char getSymbol();

	//methods
	virtual void move_on(Field &new_field) = 0;
	void setPlayer(Player &player);
};
class Rook;
class King :public Piece //Król
{
	bool moved_at_least_once;
public:
	bool Moved_at__least_once();
	King(Field *field, Player *player);
	~King() override;
	void move_on(Field &new_field) override;
	void roszada(Rook &rook);
};
class Queen :public Piece //Hetman
{
public:
	Queen(Field *field, Player *player);
	~Queen() override;
	void move_on(Field &new_field) override;
};

class Rook :public Piece //Wie¿a
{
	bool moved_at_least_once;
public:
	bool Moved_at_least_once();
	Rook(Field *field, Player *player);
	~Rook() override;
	void move_on(Field &new_field) override;
	Field *getField();
	void setField(Field new_field);
};

class Bishop :public Piece //Goniec
{
public:
	Bishop(Field *field, Player *player);
	~Bishop() override;
	void move_on(Field &new_field) override;
};

class Knight :public Piece //Skoczek
{
public:
	Knight(Field *field, Player *player);
	~Knight() override;
	void move_on(Field &new_field) override;
};

class Pawn :public Piece //Pion
{
	Field start_field;
	Field previous_field;
	bool moved_at_least_once;
public:
	Pawn(Field *field, Player *player);
	~Pawn() override;
	void move_on(Field &new_field) override;
};
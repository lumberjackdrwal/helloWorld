#pragma once

class Piece;

class Field //Klasa okreœlaj¹ca pole, na którym stoj¹ figury
{
	int x;
	int y;
	Piece *piece_on_field;
public:
	Field();
	bool isChecked;
	int getX();
	int getY();
	void setY(int new_y);
	void setX(int new_x);
	Piece *getPiece();
	void setPiece(Piece *new_piece);
};

_declspec(selectany) Field *pole = new Field[65]; //Takie rozwi¹zanie zasugerowa³a strona Microsoftu, to rozwi¹za³o problemy z dostêpem do tych obiektów
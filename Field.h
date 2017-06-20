#pragma once

class Piece;

class Field //Klasa okre�laj�ca pole, na kt�rym stoj� figury
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

_declspec(selectany) Field *pole = new Field[65]; //Takie rozwi�zanie zasugerowa�a strona Microsoftu, to rozwi�za�o problemy z dost�pem do tych obiekt�w
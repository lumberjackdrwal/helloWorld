#include "Field.h"

int Field::getX()
{
	return x;
}
int Field::getY()
{
	return y;
}
Piece *Field::getPiece()
{
	return piece_on_field;
}
void Field::setPiece(Piece *new_piece)
{
	piece_on_field = new_piece;
}
void Field::setX(int new_x)
{
	x = new_x;
}
void Field::setY(int new_y)
{
	y = new_y;
}
Field::Field() 
{
	isChecked = false;
}
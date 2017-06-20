#include "Field.h"
#include "Player.h"
#include <iostream>
#include <string>
#include <conio.h>
using namespace std;


std::string Player::getColorName()
{
	if (this->color == Color::BLACK) return "black";
	else if (this->color == Color::WHITE) return "white";
	else return "Cos poszlo nie tak przy string Player::getColorName()";
}

bool operator==(Player &that, Player &other)
{
	if (that.getColor() == other.getColor()) return true;
	else if (that.getColor() != other.getColor()) return false;
	else
	{
		std::cout << "Cos sie zepsulo przy operator== (Player &that, Player &other). Zwracam false." << std::endl;
		return false;
	}
}

bool operator!=(Player &that, Player &other)
{
	if (that.getColor() != other.getColor()) return true;
	else if (that.getColor() == other.getColor()) return false;
	else
	{
		std::cout << "Cos sie zjebalo przy operator!= (Player &that, Player &other). Zwracam false." << std::endl;
		return false;
	}
}

Color Player::getColor()
{
	return this->color;
}
void Player::setColor(Color new_color)
{
	this->color = new_color;
}
void Player::addScore(int points)
{
	this->score += points;
}
int Player::getScore()
{
	return this->score;
}
Player::Player() {}
Player::~Player() {}

Player::Player(Color color) : color(color) //zape³nia szachownicê figurami w momencie tworzenia gracza
{
	score = 0;
	if (color == BLACK)
	{
		///std::cout << "A black player is being created" << std::endl;
		Piece *czarny_krol = new King(&pole[40], this);
		Piece *czarny_hetman = new Queen(&pole[32], this);
		Piece *czarny_goniec_1 = new Bishop(&pole[24], this);
		Piece *czarny_goniec_2 = new Bishop(&pole[48], this);
		Piece *czarny_skoczek_1 = new Knight(&pole[16], this);
		Piece *czarny_skoczek_2 = new Knight(&pole[56], this);
		Piece *czarna_wieza_1 = new Rook(&pole[8], this);
		Piece *czarna_wieza_2 = new Rook(&pole[64], this);
		Piece *czarny_pionek_1 = new Pawn(&pole[7],this); /*inicjalizujê pionki w taki sposób, bo jest bardziej czytelny ni¿ tablica
														 W dodatku ka¿dy pionek ma inne, nielosowe pole startowe. Mo¿naby to rozwi¹zaæ
														 za pomoc¹ setterów i pêtli, ale z drugiej strony 8 pionków to nie a¿ tak du¿o,
														 ¿eby rezygnowaæ z zapisu czarny_pionek_n na rzecz czarny_pionek[n] */
		Piece *czarny_pionek_2 = new Pawn(&pole[15], this);
		Piece *czarny_pionek_3 = new Pawn(&pole[23], this);
		Piece *czarny_pionek_4 = new Pawn(&pole[31], this);
		Piece *czarny_pionek_5 = new Pawn(&pole[39], this);
		Piece *czarny_pionek_6 = new Pawn(&pole[47], this);
		Piece *czarny_pionek_7 = new Pawn(&pole[55], this);
		Piece *czarny_pionek_8 = new Pawn(&pole[63], this);
	}
	else if (color == WHITE)
	{
		///std::cout << "A white player is being created" << std::endl;
		Piece *bialy_krol = new King(&pole[33], this);
		Piece *bialy_hetman = new Queen(&pole[25], this);
		Piece *bialy_goniec_1 = new Bishop(&pole[17], this);
		Piece *bialy_goniec_2 = new Bishop(&pole[41], this);
		Piece *bialy_skoczek_1 = new Knight(&pole[9], this);
		Piece *bialy_skoczek_2 = new Knight(&pole[49], this);
		Piece *biala_wieza_1 = new Rook(&pole[1], this);
		Piece *biala_wieza_2 = new Rook(&pole[57], this);
		Piece *bialy_pionek_1 = new Pawn(&pole[2], this);
		Piece *bialy_pionek_2 = new Pawn(&pole[10], this);
		Piece *bialy_pionek_3 = new Pawn(&pole[18], this);
		Piece *bialy_pionek_4 = new Pawn(&pole[26], this);
		Piece *bialy_pionek_5 = new Pawn(&pole[34], this);
		Piece *bialy_pionek_6 = new Pawn(&pole[42], this);
		Piece *bialy_pionek_7 = new Pawn(&pole[50], this);
		Piece *bialy_pionek_8 = new Pawn(&pole[58], this);
	}
	else std::cout << "Cos nie wyszlo przy tworzeniu gracza" << std::endl;

}

void Player::move()
{
	Piece *bierka;
	int x_from, y_from; //Dane pobierane od u¿ytkownika, precyzuj¹ sk¹d ma siê odbyæ ruch
	cout << "Bierka: ";
	cin >> x_from >> y_from;
	if (x_from == 0 && y_from == 0)
	{
		cout << "Gracz " << this->getColorName() << " wygrywa!" << endl;
		cout << "Wynik: " << this->getScore() << endl;
		cout << "Nacisnij dowolny klawisz..." << endl;
		getch();
		exit(0);
	}
	Field *p = &pole[(x_from - 1) * 8 + y_from];
	if (p->getPiece() == nullptr)
	{
		cout << "Na tym polu nie stoi zadna bierka" << endl;
		this->addScore(-2);
		move();
		return;
	}
	else if (p->getPiece()->getPlayer() != this) //Czy bierka, ktora chcemy ruszyc, nalezy do nas?
	{
		cout << "Na tym polu stoi " << p->getPiece()->getName() << " przeciwnego gracza." << endl;
		move();
		return;
	}
	else cout << "Na tym polu stoi " << p->getPiece()->getName() << endl;
	bierka = p->getPiece();
	///cout << "bierka = p->getPiece(). p->getPiece() = " << p->getPiece()->getName() << endl;
	bierka->move_on(*getMove());

}

Field *Player::getMove()
{
	int x_to, y_to; //Dane pobierane od uzytkownika, precyzuja, dokad ma sie ruszyc bierka
	cout << "Na: ";
	cin >> x_to >> y_to;
	Field *p = &pole[(x_to - 1) * 8 + y_to];
	///cout << "getMove() zwraca pole [" << (x_to - 1) * 8 + y_to << "]" << endl;
	///cout << "p->getX() = " << p->getX() << ", getY()=" << p->getY() << endl;
	///cout << "pole[" << (x_to - 1) * 8 + y_to << "].getX()=" << pole[(x_to - 1) * 8 + y_to].getX() << ", getY()=" << pole[(x_to - 1) * 8 + y_to].getY() << endl;
	return p;
}

#include "Figury.h"
#include <cmath>
#include <string>
using std::string;
using std::cout;
using std::endl;

//Wspolrzedne na szachownicy numerowane od 1 do 8 od lewego dolnego rogu

class Player;


Piece::Piece(Field *field, Player *player) : field(field), player(player) {}
Piece::~Piece() {}
Field *Piece::getField()
{
	return this->field;
}
string Piece::getName()
{
	return this->name;
}
int Piece::get_value()
{
	return this->value;
}
Player *Piece::getPlayer()
{
	return player;
}
void Piece::setPlayer(Player &player)
{
	this->player = &player;
}
char Piece::getSymbol()
{
	return symbol;
}

King::King(Field *field, Player *player) : Piece(field, player)
{
	field->setPiece(this);
	cout << "A " << player->getColorName() << " King was created at " << field->getX() << ", " << field->getY()<< endl;
	name = "King";
	value = -1;
	symbol = 'K';
	moved_at_least_once = false;
}
King::~King() {}
void King::move_on(Field &new_field)
{
	if (this->moved_at_least_once == false) this->moved_at_least_once = true;
	if (abs(new_field.getX() - field->getX()) > 1 || abs(new_field.getY() - new_field.getY()) > 1) //nie moze ruszyc sie dalej niz 1 pole w dowolnym kierunku
	{
		cout << "Nie mozesz wykonac takiego ruchu!" << endl;
		player->addScore(-2);
		move_on(*player->getMove());
		return;
	}
	if ((new_field.getX() > 8 || new_field.getX() < 1) || (new_field.getY() > 8 || new_field.getY() < 1))
	{
		cout << "Nie mozesz wyjsc poza szachownice!" << endl;
		player->addScore(-5);
		move_on(*player->getMove());
		return;
	}
	if (new_field.getPiece() != nullptr) //sprawdza, czy na polu jest figura. Jeœli jest, nastêpuje bicie.
	{
		if (new_field.getPiece()->getPlayer() == this->field->getPiece()->getPlayer()) //czy figura ktora bijemy ma taki sam kolor jak nasza?
		{
			cout << "Na tym polu stoi juz Twoj pion!" << endl;
			player->addScore(-3);
			move_on(*player->getMove());
			return;
		}
		else if (new_field.getPiece()->getName() == "King")
		{
			cout << "Nie wolno bic krola!" << endl;
			player->addScore(-3);
			move_on(*player->getMove());
			return;
		}
		else if (new_field.isChecked == true)
		{
			cout << "To pole jest szachowane!" << endl;
			player->addScore(-1);
			move_on(*player->getMove());
			return;
		}

		cout << "Krol " << field->getX() << "." << field->getY() << " X " << new_field.getX() 
			<< "." << new_field.getY() << " " << new_field.getPiece()->getName() << "!" << endl;
		//"Krol x.y X x.y Figura!
		player->addScore(new_field.getPiece()->get_value());
		new_field.getPiece()->~Piece();
		new_field.setPiece(this);
		field->setPiece(nullptr);
		field = &new_field;
	}
	else
	{
		cout << "Krol " << field->getX() << "." << field->getY() << " -> " << new_field.getX() << "." << new_field.getY() << endl;
		field->setPiece(nullptr);
		field = &new_field;
		field->setPiece(this);
	}
}
void King::roszada(Rook &rook)
{
	if (this->moved_at_least_once == true || rook.Moved_at_least_once() == true)
	{
		cout << "Krol lub wieza wykonaly juz ruch, nie mozesz zrobic roszady. Ruch przepada." << endl;
		return;
	}
	Field new_kings_field;
	cout << "Roszada " << field->getX() << "." << field->getY() << " <-> " << new_kings_field.getX() << "." << new_kings_field.getY();
	new_kings_field = *rook.getField();
	rook.setField(*field);
	field->setPiece(&rook);
	field = &new_kings_field;
	field->setPiece(this);
}
bool King::Moved_at__least_once()
{
	if (moved_at_least_once == true) return true;
	else return false;
}

Queen::Queen(Field *field, Player *player) : Piece(field, player)
{
	field->setPiece(this);
	cout << "A " << player->getColorName() << " Queen was created at " << field->getX() << ", " << field->getY() << endl;
	name = "Queen";
	value = 9;
	symbol = 'Q';
}
Queen::~Queen() {}
void Queen::move_on(Field &new_field)
{
	if ((abs(new_field.getX() - field->getX()) != 0) && (abs(new_field.getY() - field->getY()) != 0) &&
		(abs(new_field.getY() - field->getY()) != (abs(new_field.getX() - field->getX())))) //po³¹czenie warunku wie¿y i goñca
	{
		cout << "Nie mozesz wykonac takiego ruchu!" << endl;
		player->addScore(-2);
		move_on(*player->getMove());
		return;
	}
	if ((new_field.getX() > 8 || new_field.getX() < 1) || (new_field.getY() > 8 || new_field.getY() < 1))
	{
		cout << "Nie mozesz wyjsc poza szachownice!" << endl;
		player->addScore(-5);
		move_on(*player->getMove());
		return;
	}
	if (new_field.getPiece() != nullptr) //sprawdza, czy na polu jest figura. Jeœli jest, nastêpuje bicie.
	{
		if (new_field.getPiece()->getPlayer() == this->field->getPiece()->getPlayer()) //czy figura ktora bijemy ma taki sam kolor jak nasza?
		{
			cout << "Na tym polu stoi juz Twoj pion!" << endl;
			player->addScore(-3);
			move_on(*player->getMove());
			return;
		}
		else if (new_field.getPiece()->getName() == "King")
		{
			cout << "Nie wolno bic krola!" << endl;
			player->addScore(-3);
			move_on(*player->getMove());
			return;
		}

		cout << "Hetman " << field->getX() << "." << field->getY() << " X " << new_field.getX() << "." 
			<< new_field.getY() << " " << new_field.getPiece()->getName() << "!" << endl;
		//"Hetman x.y X x.y Figura!
		player->addScore(new_field.getPiece()->get_value());
		new_field.getPiece()->~Piece();
		new_field.setPiece(this);
		field->setPiece(nullptr);
		field = &new_field;
	}
	else
	{
		cout << "Hetman " << field->getX() << "." << field->getY() << " -> " << new_field.getX() << "." << new_field.getY() << endl;
		field->setPiece(nullptr);
		field = &new_field;
		field->setPiece(this);
	}
}

Rook::Rook(Field *field, Player *player) : Piece(field, player)
{
	field->setPiece(this);
	cout << "A " << player->getColorName() << " Rook was created at " << field->getX() << ", " << field->getY() << endl;
	name = "Rook";
	value = 5;
	symbol = 'R';
}
Rook::~Rook() {}
void Rook::move_on(Field &new_field)
{

	if ((abs(new_field.getX() - field->getX()) != 0) && (abs(new_field.getY() - field->getY()) != 0))
	{
		cout << "Nie mozesz wykonac takiego ruchu!" << endl;
		player->addScore(-2);
		move_on(*player->getMove());
		return;
	}
	if ((new_field.getX() > 8 || new_field.getX() < 1) || (new_field.getY() > 8 || new_field.getY() < 1))
	{
		cout << "Nie mozesz wyjsc poza szachownice!" << endl;
		player->addScore(-5);
		move_on(*player->getMove());
		return;
	}
	if (new_field.getPiece() != nullptr) //sprawdza, czy na polu jest figura. Jeœli jest, nastêpuje bicie.
	{
		if (new_field.getPiece()->getPlayer() == this->field->getPiece()->getPlayer()) //czy figura ktora bijemy ma taki sam kolor jak nasza?
		{
			cout << "Na tym polu stoi juz Twoj pion!" << endl;
			player->addScore(-3);
			move_on(*player->getMove());
			return;
		}
		else if (new_field.getPiece()->getName() == "King")
		{
			cout << "Nie wolno bic krola!" << endl;
			player->addScore(-3);
			move_on(*player->getMove());
			return;
		}

		cout << "Wieza " << field->getX() << "." << field->getY() << " X " << new_field.getX() << "."
			<< new_field.getY() << " " << new_field.getPiece()->getName() << "!" << endl;
		//Wieza x.y X x.y Figura!
		player->addScore(new_field.getPiece()->get_value());
		new_field.getPiece()->~Piece();
		new_field.setPiece(this);
		field->setPiece(nullptr);
		field = &new_field;
	}
	else
	{
		cout << "Wieza " << field->getX() << "." << field->getY() << " -> " << new_field.getX() << "." << new_field.getY() << endl;
		field->setPiece(nullptr);
		field = &new_field;
		field->setPiece(this);
	}
}
Field *Rook::getField()
{
	return this->field;
}
void Rook::setField(Field new_field)
{
	this->field = &new_field;
}
bool Rook::Moved_at_least_once()
{
	if (moved_at_least_once == true) return true;
	else return false;
}

Bishop::Bishop(Field *field, Player *player) : Piece(field,player)
{
	field->setPiece(this);
	cout << "A " << player->getColorName() << " Bishop was created at " << field->getX() << ", " << field->getY() << endl;
	name = "Bishop";
	value = 3;
	symbol = 'B';
}
Bishop::~Bishop() {}
void Bishop::move_on(Field &new_field)
{
		if (abs(new_field.getY() - field->getY()) != (abs(new_field.getX() - field->getX())))
		{
			cout << "Nie mozesz wykonac takiego ruchu!" << endl;
			player->addScore(-2);
			move_on(*player->getMove());
			return;
		}
		if ((new_field.getX() > 8 || new_field.getX() < 1) || (new_field.getY() > 8 || new_field.getY() < 1))
		{
			cout << "Nie mozesz wyjsc poza szachownice!" << endl;
			player->addScore(-5);
			move_on(*player->getMove());
			return;
		}
		if (new_field.getPiece() != nullptr) //sprawdza, czy na polu jest figura. Jeœli jest, nastêpuje bicie.
		{
			if (new_field.getPiece()->getPlayer() == this->field->getPiece()->getPlayer()) //czy figura ktora bijemy ma taki sam kolor jak nasza?
			{
				cout << "Na tym polu stoi juz Twoj pion!" << endl;
				player->addScore(-3);
				move_on(*player->getMove());
				return;
			}
			else if (new_field.getPiece()->getName() == "King")
			{
				cout << "Nie wolno bic krola!" << endl;
				player->addScore(-3);
				move_on(*player->getMove());
				return;
			}

			cout << "Goniec " << field->getX() << "." << field->getY() << " X " << new_field.getX() << "."
				<< new_field.getY() << " " << new_field.getPiece()->getName() << "!" << endl;
			//Goniec x.y X x.y Figura!
			player->addScore(new_field.getPiece()->get_value());
			new_field.getPiece()->~Piece();
			new_field.setPiece(this);
			field->setPiece(nullptr);
			field = &new_field;
		}
		else
		{
			cout << "Goniec " << field->getX() << "." << field->getY() << " -> " << new_field.getX() << "." << new_field.getY() << endl;
			field->setPiece(nullptr);
			field = &new_field;
			field->setPiece(this);
		}
}

Knight::Knight(Field *field, Player *player) : Piece(field,player)
{
	field->setPiece(this);
	name = "Knight";
	value = 3;
	cout << "A " << player->getColorName() << " Knight was created at " << field->getX() << ", " << field->getY() << endl;
	symbol = 'H';
}
Knight::~Knight() {}
void Knight::move_on(Field &new_field)
{
	if ((new_field.getX() > 8 || new_field.getX() < 1) || (new_field.getY() > 8 || new_field.getY() < 1))
	{
		cout << "Nie mozesz wyjsc poza szachownice!" << endl;
		player->addScore(-5);
		move_on(*player->getMove());
		return;
	}
	if (new_field.getPiece() != nullptr) //sprawdza, czy na polu jest figura. Jeœli jest, nastêpuje bicie.
	{
		if (new_field.getPiece()->getPlayer() == this->field->getPiece()->getPlayer()) //czy figura ktora bijemy ma taki sam kolor jak nasza?
		{
			cout << "Na tym polu stoi juz Twoj pion!" << endl;
			player->addScore(-3);
			move_on(*player->getMove());
			return;
		}
		else if (new_field.getPiece()->getName() == "King")
		{
			cout << "Nie wolno bic krola!" << endl;
			player->addScore(-3);
			move_on(*player->getMove());
			return;
		}

		cout << "Skoczek " << field->getX() << "." << field->getY() << " X " << new_field.getX() << "."
			<< new_field.getY() << " " << new_field.getPiece()->getName() << "!" << endl;
		//Skoczek x.y X x.y Figura!
		player->addScore(new_field.getPiece()->get_value());
		new_field.getPiece()->~Piece();
		new_field.setPiece(this);
		field->setPiece(nullptr);
		field = &new_field;
		return;
	}
	if (((abs(new_field.getY() - field->getY()) == 2) && (abs(new_field.getX() - field->getX()) == 1)) ||
		((abs(new_field.getY() - field->getY()) == 1) && (abs(new_field.getX() - field->getX()) == 2)))
	{
		cout << "Skoczek " << field->getX() << "." << field->getY() << " -> " << new_field.getX() << "." << new_field.getY() << endl;
		field->setPiece(nullptr);
		field = &new_field;
		field->setPiece(this);
	}
	else
	{
		cout << "Nie mozesz wykonac takiego ruchu!" << endl;
		player->addScore(-2);
		move_on(*player->getMove());
		return;
	}
}

Pawn::Pawn(Field *field, Player *player) : Piece(field, player), start_field(*field)
{
	field->setPiece(this);
	name = "Pawn";
	value = 1;
	previous_field = start_field;
	cout << "A " << player->getColorName() << " Pawn was created at " << field->getX() << ", " << field->getY() << endl;
	symbol = 'P';
	moved_at_least_once = false;
}
Pawn::~Pawn() {}
void Pawn::move_on(Field &new_field)
{
	///cout << "new_field.getX() = " << new_field.getX() << endl;
	///cout << "new_field.getY() = " << new_field.getY() << endl;
	
	if ((new_field.getPiece() == nullptr && abs(new_field.getX()-field->getX()) != 0 )) //Pion za pierwszym razem mo¿e ruszyæ siê o 2 pola
	{
		cout << "Pion nie wykonuje takiego ruchu" << endl;
		player->addScore(-3);
		move_on(*player->getMove());
		return;
	}
	else if (new_field.getPiece() == nullptr && abs(new_field.getX() - field->getX()) != 0)
	{
		cout << "Pion nie wykonuje takiego ruchu" << endl;
		player->addScore(-3);
		move_on(*player->getMove());
		return;
	}
	if (moved_at_least_once == true && abs(new_field.getY() - field->getY()) > 1)
	{
		cout << "Pion porusza sie jedno pole do przodu!" << endl;
		player->addScore(-3);
		move_on(*player->getMove());
		return;
	}
	else if (moved_at_least_once == false && abs(new_field.getY() - field->getY()) > 2)
	{
		cout << "Pion porusza sie jedno pole do przodu!" << endl;
		player->addScore(-3);
		move_on(*player->getMove());
		return;
	}
	if ((new_field.getX() > 8 || new_field.getX() < 1) || (new_field.getY() > 8 || new_field.getY() < 1))
	{
		cout << "Nie mozesz wyjsc poza szachownice!" << endl;
		player->addScore(-5);
		move_on(*player->getMove());
		return;
	}
	if (new_field.getPiece() != nullptr && abs(new_field.getX() - field->getY()) == 1 && abs (new_field.getY() - field->getY()) == 1) //Jeœli figura jest pod skosem, nastêpuje bicie
	{
		if (new_field.getPiece()->getPlayer() == this->field->getPiece()->getPlayer()) //czy figura ktora bijemy ma taki sam kolor jak nasza?
		{
			cout << "Na tym polu stoi juz Twoj pion!" << endl;
			player->addScore(-3);
			move_on(*player->getMove());
			return;
		}
		else if (new_field.getPiece()->getName() == "King")
		{
			cout << "Nie wolno bic krola!" << endl;
			player->addScore(-3);
			move_on(*player->getMove());
			return;
		}
		cout << "Pion " << field->getX() << "." << field->getY() << " X " << new_field.getX() << "."
			<< new_field.getY() << " " << new_field.getPiece()->getName() << "!" << endl;
		//Pion x.y X x.y Figura!
		player->addScore(new_field.getPiece()->get_value());
		new_field.getPiece()->~Piece();
		new_field.setPiece(this);
		field->setPiece(nullptr);
		field = &new_field;
		moved_at_least_once = true;
	}
	else
	{
		cout << "Pion " << field->getX() << "." << field->getY() << " -> " << new_field.getX() << "." << new_field.getY() << endl;
		field->setPiece(nullptr);
		field = &new_field;
		field->setPiece(this);
		moved_at_least_once = true;
		///cout << "field->getPiece() = " << field->getPiece()->getName() << endl;
		///cout << "field->getX(),getY() = " << field->getX() << "." << field->getY() << endl;
	}
	if (field->getY() == 8 || field->getY() == 1) //czy pion doszed³ na drugi koniec szachownicy?
	{
		Piece *hetman = new Queen(field, player);
		field->setPiece(hetman); // domyœlnie zamienia na hetmana
		cout << "Pion dotarl do konca szachownicy!" << endl;
		Pawn::~Pawn();
	}
	moved_at_least_once = true;
}
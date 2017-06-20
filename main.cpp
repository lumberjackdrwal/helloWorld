#pragma once
#include "Figury.h"
#include "Field.h"
#include "Player.h"
#include <conio.h>
#include <iostream>
#include <string>
#include <windows.h>
using namespace std;

void fillFields()
{
	///pole[0].setX(666);
	///pole[0].setY(666);
	for (int x = 1, k = 1; x <= 8; x++)
	{
		for (int y = 1; y <= 8; y++, k++)
		{
			pole[(x-1)*8 + y].setX(x);
			pole[(x-1)*8 + y].setY(y);
			pole[(x - 1) * 8 + y].setPiece(nullptr);
			///cout << "pole[" << k << "] = " << (x-1)*8 + y << "    x=" << x << ", y=" << y << endl;
			///cout << "pole[" << k << "].getX()=" << pole[k].getX() << ", getY()=" << pole[k].getY() << endl;
		}
	}
}

void printChessBoard()
{
	cout << endl << endl << endl << endl << endl << endl;
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	for (int x = 8, l = 8; x >= 1; x--,l--)
	{
		cout << "   " << l << "|";
		for (int y = 1; y <= 8; y++)
		{
			if (pole[x+(8*(y-1))].getPiece() == nullptr) cout << " +";
			else
			{
				if (pole[x + (8 * (y-1))].getPiece()->getPlayer()->getColor() == Color::BLACK)
				{
					SetConsoleTextAttribute(hOut, FOREGROUND_BLUE | FOREGROUND_RED); // ustawia kolor na okolo fioletowy
				}
				else if (pole[x + (8 * (y-1))].getPiece()->getPlayer()->getColor() == Color::WHITE)
				{
					SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY); //ustawia kolor na okolo zloty
				}
				cout << " " << pole[x + (8 * (y-1))].getPiece()->getSymbol();
				SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED); //ustawia kolor na standardowy
			}
		}
		cout << "|" << endl;
	}
	cout << endl << "      1 2 3 4 5 6 7 8  " << endl << endl << endl;
}

void instrukcja()
{
	cout << endl << "==============================" << endl << endl << endl;
	cout << "Aby wykonac ruch, wpisz wspolrzedne pola, na ktorym stoi dana figura, zatwierdz" << endl;
	cout << "Nastepnie wpisz pole, na ktore ma sie przemiescic figura. Zaczyna gracz bialy." << endl;
	cout << "Pola szachownicy numerowane sa od 1 do 8 z lewej dolnej krawedzi szachownicy." << endl;
	cout << "Gdy gracze uzgodnia, ze jeden z nich wygral, podczas swojego ruchu musi wpisac 0 0" << endl << endl << endl;
}

void main_loop(Player &biale, Player &czarne)
{
	Piece *bierka;
	Field *ruch;
	int looper = 1;
	while(looper == 1)
	{
		printChessBoard();
		cout << "==Biale==" << endl;
		biale.move();
		printChessBoard();
		cout << "==Czarne==" << endl;
		czarne.move();
	}
}

int main()
{
	fillFields();
	Player biale(Color::WHITE);
	Player czarne(Color::BLACK);
	instrukcja();
	main_loop(biale,czarne);
	getch();
    return 0;
}


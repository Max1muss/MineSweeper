#pragma once
#include <iostream>
#include <ctime>
#include <algorithm>

using namespace std;

class Field
{	
	char m_field[9][9]; // массив поля
	char m_expandField[9][9]; // массив поля для работы с расширением 
	char m_displayField[9][9]; // массив поля показывающий открытые клетки игроку
	int m_borderField[11][11]; // массив для ограничения игрового поля
	int m_flags{ 0 }; // переменная для хранения количества флагов

public:

	void resetField();
	void setStart(int y, int x);
	void printStartField();
	void copyFields();
	void expand(int y, int x);
	bool isDone();
	int countMines(int y, int x);
	void putNumbers();
	//void printExpandField();
	//void print();
	void display();
	void plantMines();
	void setExpanded();
	void checkAndMark(int y, int x);
	bool checkAndOpen(int y, int x);
	bool isWin();
	int getFlags();
};


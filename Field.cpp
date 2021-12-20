#include "Field.h"


    int getRandomNumber(int min, int max) // получаем случайное число
	{
	    static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);

	    return static_cast<int>(rand() * fraction * (max - min + 1) + min);
    }

	void Field::resetField() // обнуляем массивы полей для начала игры
	{
		for (int row = 0; row < 9; ++row)
		{
			for (int column = 0; column < 9; ++column)
			{
				m_field[row][column] = 0;
			}

		}
	

	
		for (int row = 0; row < 9; ++row)
		{
			for (int column = 0; column < 9; ++column)
			{
				m_expandField[row][column] = 0;
			}

		}
	

	
		for (int row = 0; row < 9; ++row)
		{
			for (int column = 0; column < 9; ++column)
			{
				m_displayField[row][column] = 0;
			}

		}
	

	

		for (int row = 0; row < 11; ++row)
		{
			for (int column = 0; column < 11; ++column)
			{
				if ((!row) || (!column) || row == 10 || column == 10)
					m_borderField[row][column] = 0;
				else
					m_borderField[row][column] = 1;
			}

		}
	}

	void Field::setStart(int y, int x) // обозначаем начальные клетки чтобы на них нельзя было поставить бомбы
	{
		for (int it = 0; it < 3; ++it)
		{
			for (int i = 0; i < 3; ++i)
				if (m_borderField[(y + 1) - i][(x + 1) - it])
					m_field[y - i][x - it] = 'S';
		}
	}

	/*void Field::print() //вывод поля (для проверки при разработке и модификации)
	{
		for (int row = 0; row < 9; ++row)
		{
			for (int column = 0; column < 9; ++column)
			{
				cout << "|" << (m_field[row][column]);
			}

			cout << "|\n";
		}
	}

	void Field::printExpandField()  ////вывод поля (для проверки при разработке и модификации)
	{
		for (int row = 0; row < 9; ++row)
		{
			for (int column = 0; column < 9; ++column)
			{
				cout << "|" << (m_expandField[row][column]);
			}

			cout << "|\n";
		}
	}*/
	

	void Field::display() // вывод поля для игрока
	{

		cout << "\n\n\n\n\n\n                                                   Mines: " << 10 - getFlags() << "\n\n                                                1 2 3 4 5 6 7 8 9 \n                     \n";

		for (int row = 0; row < 9; ++row)
		{
			cout << "                                            " << row + 1 << "  ";
			for (int column = 0; column < 9; ++column)
			{
				cout << "|" << (m_displayField[row][column]);
			}

			cout << "|\n";
		}
	}

	void Field::printStartField() // вывод стартового поля для игрока
	{
		for (int row = 0; row < 9; ++row)
		{
			for (int column = 0; column < 9; ++column)
			{
				if (m_expandField[row][column] == 'C')
					m_displayField[row][column] = '0';
				else if (m_expandField[row][column] == 'B')
					m_displayField[row][column] = m_field[row][column];
				else
					m_displayField[row][column] = ' ';
			}
		}

		display();
	}

	void Field::expand(int y, int x) // расширяем нашу открутую зону пока встречаем 0
	{
		m_expandField[y - 1][x - 1] = 'C';

		for (int it = 0; it < 3; ++it)
		{
			for (int i = 0; i < 3; ++i)
			{
				if (m_borderField[(y + 1) - i][(x + 1) - it])
				{
				if (m_expandField[y - i][x - it] == '0')
					m_expandField[y - i][x - it] = 'Z';
				else if (m_expandField[y - i][x - it] == 'C' || m_expandField[y - i][x - it] == 'Z');
					// ignore;
					else
						m_expandField[y - i][x - it] = 'B';
				}
			}

		}
		if (!isDone()) // проверяем есть ли еще 0
		{

			for (int row = 0; row < 9; ++row)
			{
				for (int column = 0; column < 9; ++column)
				{
					if (m_expandField[row][column] == 'Z')
						expand(row + 1, column + 1);
				}
			}
		}
	}

	bool Field::isDone() // есть ли еще 0
	{
		for (int row = 0; row < 9; ++row)
		{
			for (int column = 0; column < 9; ++column)
			{
				if (m_expandField[row][column] == 'Z')
					return false;
			}
		}

		return true;
	}

	void Field::copyFields() // копируем поле для работы с ним при расширении
	{
		for (int row = 0; row < 9; ++row)
		{
			for (int column = 0; column < 9; ++column)
			{
				m_expandField[row][column] = m_field[row][column];
			}
		}
	}


	int Field::countMines(int y, int x) // считаем сколько мин вокруг данной клетки
	{
		int count = 0;

		for (int it = 0; it < 3; ++it)
		{
			for (int i = 0; i < 3; ++i)
			{
				if (m_borderField[(y + 1) - i][(x + 1) - it])
				    if (m_field[y - i][x - it] == 'X')
					    ++count;
			}
		}

		return (count + 48);
	}

	void Field::putNumbers() // ставим в клетку число мин вокруг данной клетки
	{
		for (int row = 0; row < 9; ++row)
		{
			for (int column = 0; column < 9; ++column)
			{
				if (m_field[row][column] == 'X')
					continue;
				else
				{
					m_field[row][column] = static_cast<char>(countMines((row + 1), (column + 1)));
				}
			}

		}
	}

	void Field::plantMines() // устанавливаем мины в случайном порядке
	{
		srand(static_cast<int>(time(0)));
		rand();
		
		int count = 0;
		while (count < 10)
		{
			int randX(getRandomNumber(0, 8));
			int randY(getRandomNumber(0, 8));
			if ((m_field[randX][randY] == 'S') || (m_field[randX][randY] == 'X')); // если клетка являеться стартовой или уже заминированой то переходим к следующей итерации. Если пустая то минируем.
			else
			{
				m_field[randX][randY] = 'X';
				++count;
			}
		}
	}
	void Field::setExpanded() // выводим числа игроку
	{
		for (int row = 0; row < 9; ++row)
		{
			for (int column = 0; column < 9; ++column)
			{
				if (m_expandField[row][column] == 'C')
					m_displayField[row][column] = '0';
				else if (m_expandField[row][column] == 'B')
					m_displayField[row][column] = m_field[row][column];
			}
		}
	}

	void Field::checkAndMark(int y, int x) // ставим флаг если его еще нет на этой клетке. Убираем если уже есть.
	{
		if (m_displayField[y - 1][x - 1] == ' ')
		{
			m_displayField[y - 1][x - 1] = 'F';
			++m_flags;
		}
		else if (m_displayField[y - 1][x - 1] == 'F')
		{
			m_displayField[y - 1][x - 1] = ' ';
			--m_flags;
		}
	}

	bool Field::checkAndOpen(int y, int x) // открываем эту клетку
	{
		if (m_field[y - 1][x - 1] == '0') // расширяем поле если 0
		{
			expand(y, x);
			setExpanded();
		}
		else if (m_field[y - 1][x - 1] == 'X')// если попали на мину то выводим все мины на поле и возвращаем false
		{
			for (int row = 0; row < 9; ++row)
			{
				for (int column = 0; column < 9; ++column)
				{
					if (m_field[row][column] == 'X')
						m_displayField[row][column] = m_field[row][column];
				}
			}

			return false;
		}
		else
			m_displayField[y - 1][x - 1] = m_field[y - 1][x - 1]; // выводим количество мин вокруг этой клетки

		return true;

	}

	bool Field::isWin() // проверяем есть ли еще неоткрытые клетки
	{
		for (int row = 0; row < 9; ++row)
		{
			for (int column = 0; column < 9; ++column)
			{
				if (m_displayField[row][column] == ' ')
					return false;
			}
		}

		return true;
	}

	int Field::getFlags() // возвращаем количество флагов
	{
		return m_flags;
	}


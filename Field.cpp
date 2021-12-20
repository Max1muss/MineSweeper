#include "Field.h"


    int getRandomNumber(int min, int max) // �������� ��������� �����
	{
	    static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);

	    return static_cast<int>(rand() * fraction * (max - min + 1) + min);
    }

	void Field::resetField() // �������� ������� ����� ��� ������ ����
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

	void Field::setStart(int y, int x) // ���������� ��������� ������ ����� �� ��� ������ ���� ��������� �����
	{
		for (int it = 0; it < 3; ++it)
		{
			for (int i = 0; i < 3; ++i)
				if (m_borderField[(y + 1) - i][(x + 1) - it])
					m_field[y - i][x - it] = 'S';
		}
	}

	/*void Field::print() //����� ���� (��� �������� ��� ���������� � �����������)
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

	void Field::printExpandField()  ////����� ���� (��� �������� ��� ���������� � �����������)
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
	

	void Field::display() // ����� ���� ��� ������
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

	void Field::printStartField() // ����� ���������� ���� ��� ������
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

	void Field::expand(int y, int x) // ��������� ���� �������� ���� ���� ��������� 0
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
		if (!isDone()) // ��������� ���� �� ��� 0
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

	bool Field::isDone() // ���� �� ��� 0
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

	void Field::copyFields() // �������� ���� ��� ������ � ��� ��� ����������
	{
		for (int row = 0; row < 9; ++row)
		{
			for (int column = 0; column < 9; ++column)
			{
				m_expandField[row][column] = m_field[row][column];
			}
		}
	}


	int Field::countMines(int y, int x) // ������� ������� ��� ������ ������ ������
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

	void Field::putNumbers() // ������ � ������ ����� ��� ������ ������ ������
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

	void Field::plantMines() // ������������� ���� � ��������� �������
	{
		srand(static_cast<int>(time(0)));
		rand();
		
		int count = 0;
		while (count < 10)
		{
			int randX(getRandomNumber(0, 8));
			int randY(getRandomNumber(0, 8));
			if ((m_field[randX][randY] == 'S') || (m_field[randX][randY] == 'X')); // ���� ������ ��������� ��������� ��� ��� ������������� �� ��������� � ��������� ��������. ���� ������ �� ��������.
			else
			{
				m_field[randX][randY] = 'X';
				++count;
			}
		}
	}
	void Field::setExpanded() // ������� ����� ������
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

	void Field::checkAndMark(int y, int x) // ������ ���� ���� ��� ��� ��� �� ���� ������. ������� ���� ��� ����.
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

	bool Field::checkAndOpen(int y, int x) // ��������� ��� ������
	{
		if (m_field[y - 1][x - 1] == '0') // ��������� ���� ���� 0
		{
			expand(y, x);
			setExpanded();
		}
		else if (m_field[y - 1][x - 1] == 'X')// ���� ������ �� ���� �� ������� ��� ���� �� ���� � ���������� false
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
			m_displayField[y - 1][x - 1] = m_field[y - 1][x - 1]; // ������� ���������� ��� ������ ���� ������

		return true;

	}

	bool Field::isWin() // ��������� ���� �� ��� ���������� ������
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

	int Field::getFlags() // ���������� ���������� ������
	{
		return m_flags;
	}


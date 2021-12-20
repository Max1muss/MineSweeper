#include "Field.h"

void clearCin() 
{
	if (std::cin.fail()) // ���� ���������� ���������� ��������� ���������,
	{
		std::cin.clear(); // �� ���������� cin � '�������' ����� ������
		std::cin.ignore(32767, '\n');
	}
}

bool isCorrect(int row, int col) // �������� �����
{
	if (row > 9 || row < 1 || col > 9 || col < 1)
	{
		clearCin();
			return false;
	}

	return true;
}

bool askWish() // ���������� ����� �� ����� ������ ����� ����
{
	
	cout << "Want to play again?\n'1' to play again / '2' to exit:";
	int choice;

	while (1)
	{
		cin >> choice;
		if (choice == 1)
			return true;
		else if (choice == 2)
			return false;
		else
		{
			cout << "Incorrect input\n";
			clearCin();
		}
	}
}

int main()
{

playAgain: // ��������� ���� ��� ����� ����

	Field field;
	field.resetField(); // ������������ ��� �������� �������� ������ 0
	
	int row{ 0 };
	int column{ 0 };
	int action{ 0 };

	while (!isCorrect(row, column)) // �������� ���������� ��� ������ ����
	{
		field.display();
		cout << "\n\n\n\n\n\n\n\n\n\n\n";
		cout << "Row:";
		cin >> row;
		field.display();
		cout << "\n\n\n\n\n\n\n\n\n\n\n";
		cout << "Column:";
		cin >> column;
	}
	// ����� ���� ��� �������� ���������� �� ������ ����������� ����� � ������������� ���� ��� ������ ����
	field.setStart(row, column);
	field.plantMines();
	field.putNumbers();
	field.copyFields();
	field.expand(row, column); 
	field.printStartField();

	while (1) // �������� ������� ����
	{
		row = 0;
		column = 0;

		cout << "\n\n\n\n\n\n\n\n\n\n";

		while (!isCorrect(row, column))
		{
			field.display();
			cout << "\n\n\n\n\n\n\n\n\n\n\n";
			cout << "Row:";
			cin >> row;
			field.display();
			cout << "\n\n\n\n\n\n\n\n\n\n\n";
			cout << "Column:";
			cin >> column;
		}

actionAgain:

		field.display();
		cout << "\n\n\n\n\n\n\n\n\n\n\n";
		cout << "'1' open / '2' mark:";
		cin >> action;

		if (action == 1) // ��������� ������
		{
			if (!field.checkAndOpen(row, column)) // ���� �������� false ������ ����� ��������, �������� ��� �� ���� � ���������� ����� �� �� ������ ������
			{
				field.display();
				cout << "\n\n\n\n\n\n\n\n\nBOOM!!! Unfortunatelly, you lost.\n";
				if (askWish())
					goto playAgain;
				else
					exit(0);
			}
		}
		else if (action == 2) // ������ ������ �� ��� ������
			field.checkAndMark(row, column);
		else
		{
			clearCin();
			goto actionAgain;
		}

		if (field.getFlags() == 10) // ����� ������ 10 �� ��������� �� ������� �� ��� �����
			if (field.isWin())
			{
				field.display();
				cout << "\n\n\n\n\n\n\n\n\nCongratulations, you won!\n";
				if (askWish())
					goto playAgain;
				else
					exit(0);
			}

		field.display();

	}

	return 0;
	
}

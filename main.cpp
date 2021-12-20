#include "Field.h"

void clearCin() 
{
	if (std::cin.fail()) // если предыдущее извлечение оказалось неудачным,
	{
		std::cin.clear(); // то возвращаем cin в 'обычный' режим работы
		std::cin.ignore(32767, '\n');
	}
}

bool isCorrect(int row, int col) // проверка ввода
{
	if (row > 9 || row < 1 || col > 9 || col < 1)
	{
		clearCin();
			return false;
	}

	return true;
}

bool askWish() // спрашиваем хочет ли игрок начать новую игру
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

playAgain: // переходим сюда для новой игры

	Field field;
	field.resetField(); // устанавливем все значения массивов равным 0
	
	int row{ 0 };
	int column{ 0 };
	int action{ 0 };

	while (!isCorrect(row, column)) // получаем координаты для начала игры
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
	// после того как получили координаты от игрока расставляем бомбы и устанавливаем поля для начала игры
	field.setStart(row, column);
	field.plantMines();
	field.putNumbers();
	field.copyFields();
	field.expand(row, column); 
	field.printStartField();

	while (1) // основной игровой цикл
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

		if (action == 1) // открываем клетку
		{
			if (!field.checkAndOpen(row, column)) // если вернулся false значит игрок проиграл, сообщаем ему об этом и спрашиваем хочет ли он играть заново
			{
				field.display();
				cout << "\n\n\n\n\n\n\n\n\nBOOM!!! Unfortunatelly, you lost.\n";
				if (askWish())
					goto playAgain;
				else
					exit(0);
			}
		}
		else if (action == 2) // ставим флажок на эту клетку
			field.checkAndMark(row, column);
		else
		{
			clearCin();
			goto actionAgain;
		}

		if (field.getFlags() == 10) // когда флагов 10 то проверяем не победил ли еще игрок
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

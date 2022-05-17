#include <iostream>
#include <fstream>
#include "Header.h"

// Настройка ввода
int input_from = 1; // 0 - напрямую, 1 - с консоли, 2 - с файла input.txt

//  Формат ввода:
/* 0 - пустая ячейка, 1-9 - цифра в ячейке

	1 2 3 4 5 6 7 8 9
	2 0 0 0 0 0 0 0 0
	3 0 0 0 0 0 0 0 0
	4 0 0 0 0 0 0 0 0
	5 0 0 0 0 0 0 0 0
	6 0 0 0 0 0 0 0 0
	7 0 0 0 0 0 0 0 0
	8 0 0 0 0 0 0 0 0
	9 0 0 0 0 0 0 0 0

*/

//Поля с нулями
/*
	{0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0}

	0 0 0 0 0 0 0 0 0
	0 0 0 0 0 0 0 0 0
	0 0 0 0 0 0 0 0 0
	0 0 0 0 0 0 0 0 0
	0 0 0 0 0 0 0 0 0
	0 0 0 0 0 0 0 0 0
	0 0 0 0 0 0 0 0 0
	0 0 0 0 0 0 0 0 0
	0 0 0 0 0 0 0 0 0

*/

int field[9][9] = {
		{0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0}
};

void print_field() // Просто вывод
{
	for (int i = 0; i < 81; i++)
	{
		if (i % 9 == 0 && i > 0) std::cout << std::endl;
		if (field[i / 9][i % 9] == 0) std::cout << ". "; // Нули заменяем на точки, так красивее
		else std::cout << field[i / 9][i % 9] << " ";
	}
	std::cout << std::endl;
}

bool check_line(int line, int num) // Если есть такая же цифра в линии - возвращает 0, иначе 1
{
	for (int i = 0; i < 9; i++)
	{
		if (field[i][line] == num) return 0;
	}
	return 1;
}

bool check_column(int column, int num) // Если есть такая же цифра в столбце - возвращает 0, иначе 1 
{
	for (int i = 0; i < 9; i++)
	{
		if (field[column][i] == num) return 0;
	}
	return 1;
}

bool check_square(int square, int num) // Если есть такая же цифра в квадрате - возвращает 0, иначе 1 
{
	// Нумерация квадратов:
	// 0 1 2
	// 3 4 5
	// 6 7 8

	for (int i = 0; i < 3; i++) // Строка - округлёный вниз до 0, 3 или 6 номер квадрата
	{
		for (int j = 0; j < 3; j++) // Столбец - разделенный на 3, округлёный вниз и умноженный на 3 номер квадрата
		{
			if (field[(square % 3) * 3 + i][(square / 3) * 3 + j] == num) return 0; 
		}
	}
	return 1;
}

bool check_cell(int x, int y, int num) // Если соблюдаются все условия выше, возвращает 1, иначе 0.
{
	return check_line(y, num) && check_column(x, num) && check_square(x / 3 + y / 3 * 3, num); 
}

bool find_empty_cell(int& x, int& y) { // Поиск пустой клетки. Если найдена, возвращает 1 и сохраняет координаты, иначе 0.
	for (x = 0; x < 9; x++) for (y = 0; y < 9; y++) if (field[x][y] == 0) return 1;
	return 0;
}

bool solve_field() // 1 - поле решено, 0 - решение не существует
{
	int x, y; // Координаты обрабатываемой клетки
	if (!find_empty_cell(x, y)) // Поиск пустой клетки (нуля)
		return 1; // Если всё заполнено - выходим из рекурсии
	for (int num = 1; num <= 9; num++) // Для каждой цифры
	{ 
		if (check_cell(x, y, num)) // если цифра подходит
		{ 
			field[x][y] = num; // ставим её
			if (solve_field()) return 1; // и идём дальше 
			field[x][y] = 0; // если с этой цифрой невозможно решить поле, берём следующую
		}
	}
	return 0; // Если ни одна цифра не подходит, выходим из рекурсии
}

int main()
{
	std::ifstream infile("input.txt");
	int t;

	if (input_from == 1) for (int i = 0; i < 9; i++) for (int j = 0; j < 9; j++)
	{
		std::cin >> t;
		if (t >= 0 && t <= 9) field[i][j] = t;
		else
		{
			std::cout << "Error! Wrong input" << std::endl;
			return 0;
		}
	}
	if (input_from == 2) for (int i = 0; i < 9; i++) for (int j = 0; j < 9; j++)
	{
		infile >> t;
		if (t >= 0 && t <= 9) field[i][j] = t;
		else
		{
			std::cout << "Error! Wrong input" << std::endl;
			return 0;
		}
	}

	if (solve_field()) print_field();
	else std::cout << "No solutions :(" << std::endl;
}
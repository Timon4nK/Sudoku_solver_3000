#pragma once

void print_field();
bool check_line(int line, int num);
bool check_column(int column, int num);
bool check_square(int square, int num);
bool check_cell(int x, int y, int num);
bool find_empty_cell(int& x, int& y);
bool solve_field();

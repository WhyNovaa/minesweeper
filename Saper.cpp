#include <iostream>
#include <vector>
#include <ctime>
#include <conio.h>
#include <windows.h>
#include <limits>
using namespace std;

#if defined(max)
#undef max
#endif

void print(vector<vector<pair<int, bool>>>&);

int setRandomMine(vector<vector<pair<int, bool>>>&, long long, long long);

void coolField(vector<vector<pair<int, bool>>>&, long long, long long);

bool isWin(vector<vector<pair<int, bool>>>& field, long long rows, long long columns);

bool isOpen(vector<vector<pair<int, bool>>>& field, long long row, long long column);

void realPrint(vector<vector<pair<int, bool>>>& field);

void openUnits(vector<vector<pair<int, bool>>>& field, long long rows, long long columns);

int main() 
{

	long long rows, columns, row, column, k;


	cout << "Input size of a field." << endl;
	while (true) 
	{
		cin >> rows >> columns;
		if (cin.fail() || rows <= 0 || columns <= 0) 
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Error, try again" << endl;
			continue;
		}
		else {
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			break;
		}
	}


	vector<vector<pair<int, bool>>> field(rows, vector<pair<int, bool>>(columns));
	for (long long i = 0; i < rows; i++) {
		for (long long j = 0; j < columns; j++) {
			field[i][j].first = 0;
			field[i][j].second = false;
		}
	}


	cout << "Enter number of mines." << endl;
	while (true) 
	{
		cin >> k;
		if (cin.fail() || k <= 0 || k > rows * columns) {
			cin.clear(); 
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Error, try again" << endl;
		}
		else 
		{
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			break;
		}
	}
	for (long long i = 0; i < k; i++) 
	{
		setRandomMine(field, rows, columns);
	}


	coolField(field, rows, columns);


	bool win = false;
	while (true) 
	{
		print(field);
		cout << "Enter row and column:";
		while (true) 
		{
			cin >> row >> column;
			row--;
			column--;
			if (cin.fail() || row >= rows || row < 0 || column >= columns || column < 0 || isOpen(field, row, column))
			{
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "Error, try again" << endl;
			}
			else 
			{

				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				break;
			}
		}


		if (field[row][column].first == -1)
		{
			field[row][column].second = true;
			break;
		}
		else 
		{
			field[row][column].second = true;
			openUnits(field, rows, columns);
			if (isWin(field, rows, columns)) 
			{
				win = true;
				break;
			}
			print(field);
		}
		system("CLS");
	}

	system("CLS");
	if (!win) 
	{
		print(field);
		cout << "You lost :(" << endl;
	}
	else 
	{
		cout << "You win! :)" << endl;
	}
	cout << "Opened field:" << endl;
	realPrint(field);

	return 0;
}

void print(vector<vector<pair<int, bool>>>& field)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, FOREGROUND_GREEN);

	cout << "    ";
	for (long long i = 1; i <= field[0].size(); i++) {
		cout.width(4);
		cout << i;
	}
	cout << endl;

	for (long long i = 0; i < field.size(); i++) {
		SetConsoleTextAttribute(handle, FOREGROUND_GREEN);
		cout.width(4);
		cout << i + 1;
		for (long long j = 0; j < field[0].size(); j++) {
			SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY);
			cout.width(4);
			if (field[i][j].second) {
				if (field[i][j].first == -1) {
					SetConsoleTextAttribute(handle, FOREGROUND_RED);
					cout << "*";
				}
				else {
					SetConsoleTextAttribute(handle, FOREGROUND_BLUE);
					cout << field[i][j].first;
				}
			}
			else {
				cout << "#";
			}
		}
		cout << endl;
	}
}

void realPrint(vector<vector<pair<int, bool>>>& field)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, FOREGROUND_GREEN);

	cout << "    ";
	for (long long i = 1; i <= field[0].size(); i++) {
		cout.width(4);
		cout << i;
	}
	cout << endl;
	for (long long i = 0; i < field.size(); i++) {
		SetConsoleTextAttribute(handle, FOREGROUND_GREEN);
		cout.width(4);
		cout << i + 1;
		for (long long j = 0; j < field[0].size(); j++) {
			cout.width(4);
			if (field[i][j].first == -1) 
			{
				SetConsoleTextAttribute(handle, FOREGROUND_RED);
				cout << "*";
			}
			else 
			{
				SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY);
				cout << field[i][j].first;
			}
		}
		cout << endl;
	}
}

int setRandomMine(vector<vector<pair<int, bool>>>& field, long long rows, long long columns)
{
	long long x, y;
	srand(time(NULL));
	while (true)
	{
		x = rand() % rows;
		y = rand() % columns;
		if (field[x][y].first != -1) {
			field[x][y].first = -1;
			return 0;
		}
	}
}

void coolField(vector<vector<pair<int, bool>>>& field, long long rows, long long columns)
{
	long long row_, column_, res;
	for (long long i = 0; i < rows; i++) {
		for (long long j = 0; j < columns; j++) {
			if (field[i][j].first == -1) 
			{
				continue;
			}
			res = 0;
			for (long long a = -1; a < 2; a++) {
				for (long long b = -1; b < 2; b++) {
					if (a == 0 && b == 0) {
						continue;
					}
					row_ = i + a;
					column_ = j + b;
					if (row_ >= 0 && row_ < rows && column_ >= 0 && column_ < columns) {
						if (field[row_][column_].first == -1) {
							res++;
						}
					}
				}
			}
			field[i][j].first = res;
		}
	}
}

bool isWin(vector<vector<pair<int, bool>>>& field, long long rows, long long columns)
{
	for (long long i = 0; i < rows; i++) {
		for (long long j = 0; j < columns; j++) {
			if (!field[i][j].second && field[i][j].first != -1) {
				return false;
			}
		}
	}
	return true;
}

bool isOpen(vector<vector<pair<int, bool>>>& field, long long row, long long column) 
{
	return field[row][column].second;
}

void openUnits(vector<vector<pair<int, bool>>>& field, long long rows, long long columns) 
{
	long long row_, column_;
	bool flag = true;
	while (flag) {
		flag = false;
		for (long long i = 0; i < rows; i++) {
			for (long long j = 0; j < columns; j++) {
				if (field[i][j].first == 0 && field[i][j].second) {
					for (int a = -1; a < 2; a++) {
						for (int b = -1; b < 2; b++) {
							if (a == 0 && b == 0) {
								continue;
							}
							row_ = i + a;
							column_ = j + b;
							if (row_ >= 0 && row_ < rows && column_ >= 0 && column_ < columns) {
								if (field[row_][column_].first == 0 && !field[row_][column_].second) {
									flag = true;
								}
								field[row_][column_].second = true;
							}
						}
					}
				}
			}
		}
	}
}


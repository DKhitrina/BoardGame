#include <iostream>

using namespace std;

class Board {
	int arraysize;
	char** arrayidx;
	int check_diag_1(int x, int y);
	int check_diag_2(int x, int y);
	int check_vert(int x, int y);
	int check_goriz(int x, int y);
public:
	Board(int size);		//create desk with given average
	~Board();			//delete desk
	void AddPoint(int playernumber, int cord_x, int cord_y);
	void PrintDesk();
	int Check(int cord_x, int cord_y);		//check for winning situation
};

/*
class Player {
	int player_number;
	char player_sign;						// how player will be prodused on a board
public:
	Player(int numb, char sign);
	~Player();
	int GetNumber();
	void Move(Board b, int x, int y);	// тут где-то должны быть ссылки потому что доска должна изменяться
	void ShowBoard(Board b);
};*/

int Board::check_diag_1(int x, int y)
{
	int i = 0;
	int j = 0;
	int count = 0;
	int flag = 0;
	char a = arrayidx[x][y];

	if (x >= 4 && y >= 4) {
		i = x - 4; j = y - 4;
	}
	else 
		if (x >= y)
			i = x - y;
	else 
		j = y - x;
	for (int k = 0; k < 9 && j + k < arraysize && i + k < arraysize; k++)
		if (arrayidx[i + k][j + k] == a)
		{
			count++;
			if (count == 5)
				flag = 1;
		}
		else
			count = 0;
	return flag;
}

int Board::check_diag_2(int x, int y)  //шкипер, у нас проблема
{
	char a = arrayidx[x][y];
	int i = 0, j = 0, count = 0, flag = 0;
	if (x >= 4 && y <= arraysize - 5) {
		i = x - 4; j = y - 4;
	}
	else if (x >= arraysize - y) {
		j = arraysize - 1;
		i = x - (arraysize - y) + 1;
	}
	else {
		j = y + x;
	}

	for (int k = 0; k < 9 && i + k < arraysize && j - k > 0; k++)
		if (arrayidx[i + k][j - k] == a)
		{
			count++;
			if (count == 5)
				flag = 1;
		}
		else
			count = 0;
	return flag;
}

int Board::check_vert(int x, int y)
{
	char a = arrayidx[x][y];
	int j = 0, count = 0, flag = 0;
	if (y >= 4)
		j = y-4;
	for (int k = 0; k < 9 && j + k < arraysize; k++)
		if (arrayidx[x][j + k] == a)
		{
			count++;
			if (count == 5)
				flag = 1;
		}
		else
			count = 0;
	return flag;
}

int Board::check_goriz(int x, int y)
{
	char a = arrayidx[x][y];
	int i = 0, count = 0, flag = 0;
	if (x >= 4)
		i = x - 4;
	for (int k = 0; k < 9 && i + k < arraysize; k++)
		if (arrayidx[i + k][y] == a)
		{
			count++;
			if (count == 5)
				flag = 1;
		}
		else
			count = 0;
	return flag;
}

Board::Board(int size)
{
	arraysize = size;
	char **dynamic_array = new char*[arraysize];
	for (int i = 0; i < arraysize; i++)
		dynamic_array[i] = new char[arraysize];
	arrayidx = dynamic_array;
	for (int i = 0; i < arraysize; i++)
		for (int j = 0; j < arraysize; j++)
			dynamic_array[i][j] = '-';
}

Board::~Board()
{
	for (int i = 0; i < arraysize; i++)
		delete[] arrayidx[i];
}

void Board::AddPoint(int playernumber, int cord_x, int cord_y)
{
	if (playernumber == 1)
		arrayidx[cord_x][cord_y] = 'X';
	else
		arrayidx[cord_x][cord_y] = 'O';
}

void Board::PrintDesk()
{
	cout << "  ";
	for (int i = 0; i < arraysize; i++)
		cout << i;
	cout << "\n";
	for (int i = 0; i < arraysize; i++) {
		cout << i << " ";
		for (int j = 0; j < arraysize; j++)
			cout << arrayidx[j][i];
		cout << "\n";
	}
}

int Board::Check(int cord_x, int cord_y)
{
	if (check_diag_1(cord_x, cord_y) + check_diag_2(cord_x, cord_y)
		+ check_goriz(cord_x, cord_y)
		+ check_vert(cord_x, cord_y) >= 1)
		return 1;
	else
		return 0;
}


int main()
{
	int desksize;
	int i = 0;
	cout << "Game 'five in a row'. Please enter the size of square playing "
		<<"field, (integer >5)\n";
	cin >> desksize;
	Board d(desksize);
	cout << "Rules: Players take turns setting points on the field. The goal"
		<< " is to put five points in a row faster than the opponent.\n"
		<< "Please enter the cordinates of the point separated by a space,"
		<< " first a column, then a line\n";
	d.PrintDesk();
	while (i < desksize * desksize) 				//main game cycle
	{
		int pl_num, cord_x, cord_y;
		if (i % 2 == 0)								//who is playing
			pl_num = 1;
		else
			pl_num = 2;
		cout << "Player " << pl_num << ":\n";		//invite player
		cin >> cord_x >> cord_y;					//take coordinates from player
		d.AddPoint(pl_num, cord_x, cord_y);
		d.PrintDesk();
		if (d.Check(cord_x, cord_y) == 1)							//check for winning situation
		{
			cout << "GAME IS OVER. THE WINNER IS PLAYER " << pl_num << "\n";
			break;
		}
		i++;										//next move
	}
	if (i == desksize * desksize)					//situation of draw
	cout << "GAME IS OVER. DRAW\n";
	return 0;
}
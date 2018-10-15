#include <iostream>

using namespace std;

class Desk {
private:
	int arraysize;
	int** arrayidx;
	int check_diag_1(int x, int y);
	int check_diag_2(int x, int y);
	int check_vert(int x, int y);
	int check_goriz(int x, int y);
public:
	Desk(int size);		//create desk with given average
	~Desk();			//delete desk
	void AddPoint(int playernumber, int cord_x, int cord_y);
	void PrintDesk();
	int Check(int cord_x, int cord_y);		//check for winning situation
};

int Desk::check_diag_1(int x, int y)
{
	int i = 0;
	int j = 0;
	int count = 0;
	int flag = 0;
	int a = arrayidx[x][y];

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

int Desk::check_diag_2(int x, int y)  //шкипер, у нас проблема
{
	int a = arrayidx[x][y];
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

int Desk::check_vert(int x, int y)
{
	int a = arrayidx[x][y];
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

int Desk::check_goriz(int x, int y)
{
	int a = arrayidx[x][y];
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

Desk::Desk(int size)
{
	arraysize = size;
	int **dynamic_array = new int*[arraysize];
	for (int i = 0; i < arraysize; i++)
		dynamic_array[i] = new int[arraysize];
	arrayidx = dynamic_array;
	for (int i = 0; i < arraysize; i++)
		for (int j = 0; j < arraysize; j++)
			dynamic_array[i][j] = '-';
}

Desk::~Desk()
{
	for (int i = 0; i < arraysize; i++)
		delete[] arrayidx[i];
}

void Desk::AddPoint(int playernumber, int cord_x, int cord_y)
{
	if (playernumber == 1)
		arrayidx[cord_x][cord_y] = 'X';
	else
		arrayidx[cord_x][cord_y] = 'O';
}

void Desk::PrintDesk()
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

int Desk::Check(int cord_x, int cord_y)
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
	Desk d(desksize);
	cout << "Rules: Players take turns setting points on the field. The goal"
		<< " is to put five points in a row faster than the opponent.\n"
		<< "Please enter the cordinates of the point separated by a space,"
		<< " first a column, then a line\n";
	d.PrintDesk();
	/*while (i < desksize * desksize) 				//main game cycle
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
			cout << "GAME IS OVER. THE WINNER IS PLAYER " << pl_num << "\n");
			break;
		}
		i++;										//next move
	}
	if (i == desksize * desksize)					//situation of draw
	*/	cout << "GAME IS OVER. DRAW\n";
	return 0;
}
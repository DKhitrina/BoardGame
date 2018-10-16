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
	int AddPoint(char playersign, int cord_x, int cord_y);
	void PrintBoard();
	bool Check(int cord_x, int cord_y);		//check for winning situation
};

class Player {
	int player_number;
	char player_sign;						// how player will be prodused on a board
public:
	Player();
	Player(int numb, char sign);
	int Move(Board &b, int x, int y);
	//virtual void AnalyseBoard(Board b);
};

class Arbitrator {
	int number_of_players;
	int current_player;
	Player* players_array;
public:
	Arbitrator(int numb);
	~Arbitrator();
	Player Turn();
	int GetTurnNumber() { return current_player; }
	Player GetPlayer() { return players_array[current_player-1]; }
};

Arbitrator::Arbitrator(int numb)
{
	number_of_players = numb;
	current_player = 1;
	Player* pl = new Player[number_of_players];
	players_array = pl;
	for (int i = 0; i < number_of_players; i++)
	{
		Player p(i+1, 65+i);		//65 - ASCII code for 'A'
		pl[i] = p;
	}
}

Arbitrator::~Arbitrator()
{
	delete[] players_array;
}

Player Arbitrator::Turn()
{
	if (current_player < number_of_players)
		current_player++;
	else
		current_player = 1;
	return players_array[current_player-1];
}

Player::Player()
{
	player_number = 0;
	player_sign = 0;
}

Player::Player(int numb, char sign)
{
	player_number = numb;
	player_sign = sign;
}

int Player::Move(Board &b, int x, int y)
{
	return b.AddPoint(player_sign, x, y);
}

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

int Board::AddPoint(char playersign, int cord_x, int cord_y)
{
	if (cord_x >= arraysize || cord_y >= arraysize)
		return 1;
	if (arrayidx[cord_x][cord_y] == '-')
	{
			arrayidx[cord_x][cord_y] = playersign;
			return 0;
	}
	else
		return 1;
}

void Board::PrintBoard()
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

bool Board::Check(int cord_x, int cord_y)
{
	return(check_diag_1(cord_x, cord_y) || check_diag_2(cord_x, cord_y)
		|| check_goriz(cord_x, cord_y)
		|| check_vert(cord_x, cord_y));
}


int main()
{
	int desksize, playersnumber;
	bool flag;
	int i = 0;
	cout << "Game 'five in a row'. Please enter the size of square playing "
		<<"field, (integer >5)\n";
	cin >> desksize;
	Board d(desksize);
	cout << "How many players there would be? \n";
	cin >> playersnumber;
	Arbitrator a(playersnumber);

	cout << "Rules: Players take turns setting points on the field. The goal"
		<< " is to put five points in a row faster than the opponent.\n"
		<< "Please enter the cordinates of the point separated by a space,"
		<< " first a column, then a line\n";
	d.PrintBoard();
	Player pl = a.GetPlayer();
	while (i < desksize * desksize) 				//main game cycle
	{
		int cord_x, cord_y;
		cout << "Player " << a.GetTurnNumber() << ":\n";		//invite player

		cin >> cord_x >> cord_y;					//take coordinates from player
		if (pl.Move(d, cord_x, cord_y) == 1)
			cout << "Please input correct coordinates next time\n";
		d.PrintBoard();
		if (d.Check(cord_x, cord_y) == 1)			//check for winning situation
		{
			cout << "GAME IS OVER. THE WINNER IS PLAYER " 
				<< a.GetTurnNumber() << "\n";
			flag = 1;
			break;
		}
		pl = a.Turn();						//choose new player
		i++;										//next move
	}
	if (i == desksize * desksize && !flag)					//situation of draw
		cout << "GAME IS OVER. DRAW\n";
	cin >> desksize;
	return 0;
}
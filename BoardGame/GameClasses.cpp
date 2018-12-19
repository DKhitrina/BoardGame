#include <iostream>
#include "GameClasses.h"

using namespace std;


Arbitrator::Arbitrator(Board *b)
{
	board = b;
	number_of_players = 0;
	current_player = 1;
	players_array = 0;
}

Arbitrator::~Arbitrator()
{
	if (players_array)
		delete[] players_array;
}

void Arbitrator::AddPlayer(Player* p)
{
	//	players_array[number_of_players] = p;
	number_of_players++;

	if (players_array == 0)
	{
		players_array = new Player*[1];
		players_array[0] = p;
	}
	else
	{
		Player** pl = new Player*[number_of_players];
		//	Player* p2 = players_array;							
		for (int i = 0; i < number_of_players - 1; i++)
		{
			pl[i] = players_array[i];
		}
		pl[number_of_players - 1] = p;
		//	delete[] p2;										//new
		players_array = pl;
	}
}

void Arbitrator::Turn()
{
	if (current_player < number_of_players)
		current_player++;
	else
		current_player = 1;
}

void Arbitrator::Run()
{
	cout << "Rules: Players take turns setting points on the field. The goal"
		<< " is to put five points in a row faster than the opponent.\n"
		<< "Please enter the cordinates of the point separated by a space,"
		<< " first a column, then a line\n";

	while (!(board->CheckIfDraw())) 		//main game cycle
	{
		if (GetPlayer()->Move(board) == 1)
			cout << "Please input correct coordinates next time\n";

		if (board->IsWinFlag())			//check for winning situation
		{
			board->PrintBoard();
			cout << "GAME IS OVER. THE WINNER IS PLAYER "
				<< GetTurnNumber() << "\n";
			break;
		}
		Turn();						//choose new player
	}
	if (board->CheckIfDraw() && !board->IsWinFlag())	//situation of draw
	{
		board->PrintBoard();
		cout << "GAME IS OVER. DRAW\n";
	}
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

int Player::Move(Board *b)
{
	int x, y;
	b->PrintBoard();
	cout << "Player " << GetPlayerNumber() << ": ";		//invite player
	cin >> x >> y;					//take coordinates from player
	return b->AddPoint(player_sign, x, y);
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

int Board::check_diag_2(int x, int y)
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
		j = y - 4;
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

void Board::init(int size)
{
	occupied_points = 0;
	arraysize = size;
	win_flag = 0;
	possible_bot_moves = 0;
	if (size > 0)
	{
		char **dynamic_array = new char*[arraysize];
		for (int i = 0; i < arraysize; i++)
			dynamic_array[i] = new char[arraysize];
		arrayidx = dynamic_array;
		for (int i = 0; i < arraysize; i++)
			for (int j = 0; j < arraysize; j++)
				dynamic_array[i][j] = '-';

	}
	else
		arrayidx = 0;
}

void Board::update_bot_moves(int x, int y)
{
   // добавить окрестность точки в досягаемые
   delete_bot_move(x, y);

   add_bot_move(x+1, y+1);
   add_bot_move(x+1, y);
   add_bot_move(x+1, y-1);
   add_bot_move(x, y+1);
   add_bot_move(x-1, y-1);
   add_bot_move(x-1, y);
   add_bot_move(x, y-1);
   add_bot_move(x-1, y+1);
}

void Board::add_bot_move(int x, int y)
{
	if (x>=0 && y>=0 && x<arraysize && y<arraysize && arrayidx[x][y] == '-')
	{
		// проверка не было ли уже такой точки в списке
		struct bot_moves* bm1 = possible_bot_moves;
		bool f = 0;
		while (bm1 != 0)
		{
			if (bm1->x == x && bm1->y == y)
			{
				f = 1;
				break;
			}
			bm1 = bm1->next;
		}
		//добавление точки, если таковой еще не было
		if (!f)
		{
			struct bot_moves* bm2 = new bot_moves;
//			bm2->weight_attaсk = calculate_attack();
//			bm2->weight_defence = calculate_defence();
			bm2->x = x;
			bm2->y = y;
			bm2->next = 0;
			if (possible_bot_moves == 0)
				possible_bot_moves = bm2;
			else
			{
				struct bot_moves* bm3 = possible_bot_moves;
				while (bm3->next != 0)
					bm3 = bm3->next;
				bm3->next = bm2;
			}
		}
	}
}

void Board::delete_bot_move(int x, int y)
{
	struct bot_moves* bm4 = possible_bot_moves;
	if (bm4 != 0)		// to avoid exeption after first move
	{	//find element to delete
		while (1)
		{
			if (bm4 == 0 || bm4->x == x && bm4->y == y)
				break;
			bm4 = bm4->next;
		}
		// delete element bm4
		if (bm4 != 0)
		{
			struct bot_moves* bm_delete = bm4;
			if (bm4 != possible_bot_moves)
			{
				struct bot_moves* bm_prev = possible_bot_moves;
				while (bm_prev->next != bm4)
					bm_prev = bm_prev->next;
				if (bm4->next != 0)
				{
					bm4 = bm4->next;
					bm_prev->next = bm4;
				}
				else
					bm_prev->next = 0;
			}
			else
				possible_bot_moves = bm4->next;
			delete bm_delete;
		}
	}
}

/*int Board::calculate_attack()
{

}

int Board::calculate_defence()
{

}*/

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
		occupied_points++;
		if (CheckIfWin(cord_x, cord_y) == 1)
			win_flag = 1;
		update_bot_moves(cord_x, cord_y);
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

bool Board::CheckIfWin(int cord_x, int cord_y)
{
	return(check_diag_1(cord_x, cord_y) || check_diag_2(cord_x, cord_y)
		|| check_goriz(cord_x, cord_y)
		|| check_vert(cord_x, cord_y));
}


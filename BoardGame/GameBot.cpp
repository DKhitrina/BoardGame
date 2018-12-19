#include "GameClasses.h"
#include "GameBot.h"

#include <iostream>
#include <cstdlib>


using namespace std;

int PlayerBot::get_template_value(int templ)
{
	if (templ == FIVEROW)
		return FIVEROW_W;
	if (templ == OPENFOUR)
		return OPENFOUR_W;
	if (templ == HFOPENFOUR)
		return HFOPENFOUR_W;
	if (templ == OPENTHREE)
		return OPENTHREE_W;
	if (templ == HFOPENTHREE)
		return HFOPENTHREE_W;
	if (templ == OPENTWO)
		return OPENTWO_W;
	return 0;
}

int* PlayerBot::get_template_array(int templ)
{
	if (templ == FIVEROW) {
		int ar2[5] = { 1,1,1,1,1 };
		return ar2;
	}
	if (templ == OPENFOUR){
		int ar2[6] = { 0,1,1,1,1,0 };
		return ar2;
	}
	if (templ == HFOPENFOUR){
		int ar2[6] = { 0,1,1,1,1,2 };
		return ar2;
	}
	if (templ == OPENTHREE){
		int ar2[5] = { 0,1,1,1,0 };
		return ar2;
	}
	if (templ == HFOPENTHREE){
		int ar2[5] = { 0,1,1,1,2 };
		return ar2;
	}
	if (templ == OPENTWO){
		int ar2[4] = { 0,1,1,0 };
		return ar2;
	}
	return 0;
}

int PlayerBot::check_template(int templ, int ar[])
{
	//переведем шаблон в массив
	int i = 0;
	int* ar2 = get_template_array(templ);
	for (i = 0; ar2[i] >= 0; i++) {}
		

	// i - длина шаблона
	//будем сравнивать два массива в одну сторону ..
	bool flag = true;
	for (int k = 0; k <= 9 - i; k++)
	{
		flag = true;
		for (int l = 0; l < i; l++)
		{
			if (ar[k + l] != ar2[l])
				flag = false;
		}
		if (flag)
			break;
	}
	if (flag)
		return get_template_value(templ);
	// .. и в другую сторону
	for (int k = 0; k <= 9 - i; k++)
	{
		flag = true;
		for (int l = 0; l < i; l++)
		{
			if (ar[k + l] != ar2[i-l])
				flag = false;
		}
		if (flag)
			break;
	}
	if (flag)
		return get_template_value(templ);
	return 0;
}

int PlayerBot::vert_weight(int x, int y, char** board, char player_sign)
{
	int ar[9];
	char ch = player_sign;

	//сделаем массив из значений окрестности 4 нашей точки
	for (int i = 0; i < 9; i++)
	{
		if (y - 4 + i < 0 || y - 4 + i > DESKSIZE - 1)
			ar[i] = 2;
		else
			if (i == 4)
				ar[i] = 1;
		else {
			if (board[x][y - 4 + i] == ch)
				ar[i] = 1;
			else 
			{
				if (board[x][y - 4 + i] == '-')
					ar[i] = 0;
				else
					ar[i] = 2;
			}					
		}
	}
	return check_template(FIVEROW, ar)+check_template(OPENFOUR, ar) + check_template(HFOPENFOUR, ar) +
		check_template(OPENTHREE, ar) + check_template(HFOPENTHREE, ar) + check_template(OPENTWO, ar);
}

int PlayerBot::goriz_weight(int x, int y, char** board, char player_sign)
{
	int ar[9];
	char ch = player_sign;

	//сделаем массив из значений окрестности 4 нашей точки
	for (int i = 0; i < 9; i++)
	{
		if (x - 4 + i < 0 || x - 4 + i > DESKSIZE - 1)
			ar[i] = 2;
		else
			if (i == 4)
				ar[i] = 1;
			else {
				if (board[x-4+i][y] == ch)
					ar[i] = 1;
				else
				{
					if (board[x-4+i][y] == '-')
						ar[i] = 0;
					else
						ar[i] = 2;
				}
			}
	}
	return check_template(FIVEROW, ar) + check_template(OPENFOUR, ar) + check_template(HFOPENFOUR, ar) +
		check_template(OPENTHREE, ar) + check_template(HFOPENTHREE, ar) + check_template(OPENTWO, ar);
}

int PlayerBot::diag1_weight(int x, int y, char** board, char player_sign)
{
	int ar[9];
	char ch = player_sign;

	//сделаем массив из значений окрестности 4 нашей точки
	for (int i = 0; i < 9; i++)
	{
		if (x - 4 + i < 0 || x - 4 + i > DESKSIZE - 1 || y - 4 + i < 0 || y - 4 + i > DESKSIZE - 1)
			ar[i] = 2;
		else
			if (i == 4)
				ar[i] = 1;
			else {
				if (board[x - 4 + i][y - 4 + i] == ch)
					ar[i] = 1;
				else
				{
					if (board[x - 4 + i][y - 4 + i] == '-')
						ar[i] = 0;
					else
						ar[i] = 2;
				}
			}
	}
	return check_template(FIVEROW, ar) + check_template(OPENFOUR, ar) + check_template(HFOPENFOUR, ar) +
		check_template(OPENTHREE, ar) + check_template(HFOPENTHREE, ar) + check_template(OPENTWO, ar);
}

int PlayerBot::diag2_weight(int x, int y, char** board, char player_sign)
{
	int ar[9];
	char ch = player_sign;

	//сделаем массив из значений окрестности 4 нашей точки
	for (int i = 0; i < 9; i++)
	{
		if (x - 4 + i < 0 || x - 4 + i > DESKSIZE - 1 || y + 4 - i < 0 || y + 4 - i > DESKSIZE - 1)
			ar[i] = 2;
		else
			if (i == 4)
				ar[i] = 1;
			else {
				if (board[x - 4 + i][y + 4 - i] == ch)
					ar[i] = 1;
				else
				{
					if (board[x - 4 + i][y + 4 - i] == '-')
						ar[i] = 0;
					else
						ar[i] = 2;
				}
			}
	}
	return check_template(FIVEROW, ar) + check_template(OPENFOUR, ar) + check_template(HFOPENFOUR, ar) +
		check_template(OPENTHREE, ar) + check_template(HFOPENTHREE, ar) + check_template(OPENTWO, ar);
}

int PlayerBot::calculate_attack(int x, int y, char** board)
{
	return vert_weight(x,y,board,'O') + goriz_weight(x, y, board, 'O') + diag1_weight(x, y, board, 'O') + diag2_weight(x, y, board, 'O');
}

int PlayerBot::calculate_defence(int x, int y, char** board)
{
	return vert_weight(x, y, board, 'X') + goriz_weight(x, y, board, 'X') + diag1_weight(x, y, board, 'X') + diag2_weight(x, y, board, 'X');
}

PlayerBot::PlayerBot(): Player() {}

PlayerBot::PlayerBot(int numb, char sign): Player(numb, sign) {}

int PlayerBot::Move(Board *b)
{
	int x = 0, y = 0;
	int max_weight = 0;
	b->PrintBoard();
	char** brd = b->GetBoard();
	struct bot_moves* bot_m = b->GetBotMoves(); // получаем список всех возможных ходов

	if (bot_m != 0)
	{
		struct bot_moves* bot_m2 = bot_m;
		while (bot_m2 != 0)		//считаем значения весов и одновременно выбираем наибольший
		{
			bot_m2->weight = calculate_attack(bot_m2->x, bot_m2->y, brd)
				+ calculate_defence(bot_m2->x, bot_m2->y, brd);
			if (bot_m2->weight > max_weight)
			{
				max_weight = bot_m2->weight;
				x = bot_m2->x; y = bot_m2->y;	//запоминаем сразу координаты наиболее весомого хода
			}
			bot_m2 = bot_m2->next;
		}
		// если через веса оптимизировать ход не удалось, то ходим рандомно
		if (max_weight == 0)
		{
			int i = 0;
			bot_m2 = bot_m;
			while (bot_m2 != 0)
			{
				bot_m2 = bot_m2->next;
				i++;
			}
			int j = rand() % i;
			bot_m2 = bot_m;
			for (i = 0; i < j; i++)
				bot_m2 = bot_m2->next;
			x = bot_m2->x; y = bot_m2->y;
		}
	}
	cout << "Bot move: " << x << " " << y << "\n";
	cout << "Weight: " << max_weight << "\n";
	return b->AddPoint(GetSign(), x, y);
}

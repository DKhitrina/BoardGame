#include "GameClasses.h"
#include "GameBot.h"

#include <iostream>
#include <cstdlib>

using namespace std;

PlayerBot::PlayerBot(): Player() {}

PlayerBot::PlayerBot(int numb, char sign): Player(numb, sign) {}

int PlayerBot::Move(Board *b)
{
	int x, y;
	b->PrintBoard();


	struct bot_moves* bot_m = b->GetBotMoves();
	struct bot_moves* bot_m2 = bot_m;
	int i = 1;
	while (bot_m2->next != 0)
	{
		i++;
		bot_m2 = bot_m2->next;
	}
	int j = rand() % i;
	bot_m2 = bot_m;
	for (i = 0; i<j; i++)
		bot_m2 = bot_m2->next;
	x = bot_m2->x; y = bot_m2->y;

	
	/* THERE SHOULD BE ANALYSING ALGORYTHM
1. создать массив из возможных ходов в окрестности 1 от уже занятых точек и рандомно на них ходить. проверить 
правильность работы этого массива
	cout << "Bot " << GetPlayerNumber() << ":\n";		//invite player
	cin >> x >> y;					//take coordinates from player
	
	x = (int)(rand() / RAND_MAX * b->GetBoardSize());
	y = (int)(rand() / RAND_MAX * b->GetBoardSize());

	*/

	cout << "Bot move: " << x << " " << y << "\n";
	return b->AddPoint(GetSign(), x, y);
}
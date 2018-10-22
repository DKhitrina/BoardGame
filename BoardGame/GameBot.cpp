#include "GameClasses.h"
#include "GameBot.h"

#include <iostream>

using namespace std;

PlayerBot::PlayerBot(): Player() {}

PlayerBot::PlayerBot(int numb, char sign): Player(numb, sign) {}

int PlayerBot::Move(Board *b)
{
	int x, y;
	b->PrintBoard();

	/*
	cout << "Bot " << GetPlayerNumber() << ":\n";		//invite player
	cin >> x >> y;					//take coordinates from player
	
	x = (int)(rand() / RAND_MAX * b->GetBoardSize());
	y = (int)(rand() / RAND_MAX * b->GetBoardSize());

	*/
	cout << x << ":" << y;
	

	return b->AddPoint(GetSign(), x, y);
}
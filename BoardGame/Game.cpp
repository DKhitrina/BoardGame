#include <iostream>
#include "GameClasses.h"
#include "GameBot.h"
//#define DESKSIZE 10 ג פאיכו GameBot.h

using namespace std;


int main()
{
	int desksize = DESKSIZE;

//	cout << "Game 'five in a row'. Please enter the size of square playing "
//		<<"field, (integer >5)\n";
//	cin >> desksize;

	Board d(desksize);

	Player p1 = Player(1, 'X');
	PlayerBot p2 = PlayerBot(2, 'O');

	Arbitrator a(&d);
	a.AddPlayer(&p1);
	a.AddPlayer(&p2);

	a.Run();

	cin >> desksize;

	return 0;
}
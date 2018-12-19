#pragma once
#include "GameClasses.h"

class PlayerBot : public Player {
//	int MiniMax ();
//	bool IsTerminal();
//	int EvaluateBoardStatus();
public:
	PlayerBot();
	PlayerBot(int numb, char sign);
	int Move(Board *b);
};

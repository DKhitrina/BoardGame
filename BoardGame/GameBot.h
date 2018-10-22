#pragma once
#include "GameClasses.h"

class PlayerBot : public Player {
public:
	PlayerBot();
	PlayerBot(int numb, char sign);
	int Move(Board *b);
};


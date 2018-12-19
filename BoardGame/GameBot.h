#pragma once
#include "GameClasses.h"

#define DESKSIZE 10

#define FIVEROW 11111
#define OPENFOUR 011110
#define	HFOPENFOUR 011112
#define OPENTHREE 01110
#define HFOPENTHREE 01112
#define OPENTWO 0110

#define FIVEROW_W 9999
#define OPENFOUR_W 7000
#define	HFOPENFOUR_W 4000
#define OPENTHREE_W 3000
#define HFOPENTHREE_W 1500
#define OPENTWO_W 200


class PlayerBot : public Player {
	int get_template_value(int templ);
	int* get_template_array(int templ);
	int check_template(int templ, int a[]);
	int vert_weight(int x, int y, char** board, char player_sign);
	int goriz_weight(int x, int y, char** board, char player_sign);
	int diag1_weight(int x, int y, char** board, char player_sign);
	int diag2_weight(int x, int y, char** board, char player_sign);
	int calculate_attack(int x, int y, char** board);
	int calculate_defence(int x, int y, char** board);
public:
	PlayerBot();
	PlayerBot(int numb, char sign);
	int Move(Board *b);
};

#pragma once

	struct bot_moves{
//		int weight_attaсk;		// по умолчанию 0, выставляется в зависимости от нападения или защиты
//		int weight_defence;
		int x;
		int y;
		bot_moves* next;
	};

class Board {
	int arraysize;
	char** arrayidx;
	int occupied_points;
	bool win_flag;
	int check_diag_1(int x, int y);
	int check_diag_2(int x, int y);
	int check_vert(int x, int y);
	int check_goriz(int x, int y);
	struct bot_moves* possible_bot_moves;
	void update_bot_moves(int x, int y);
	void add_bot_move(int x, int y);
	void delete_bot_move(int x, int y);
//	int calculate_attack();
	//int calculate_defence();
protected:
	bool CheckIfWin(int cord_x, int cord_y);		//check for winning situation
	void init(int size);
public:
	Board() { init(0); }
	Board(int size) { init(size); }					//create desk with given average
	~Board();										//delete desk
	int AddPoint(char playersign, int cord_x, int cord_y);
	void PrintBoard();
	char** GetBoard() { return arrayidx; }
	int GetBoardSize() { return arraysize; }
	bot_moves* GetBotMoves() { return possible_bot_moves; }
	bool IsWinFlag() { return win_flag; }
	bool CheckIfDraw() { return occupied_points >= arraysize * arraysize; }
};

class Player {
	int player_number;
	char player_sign;						// how player will be prodused on a board
public:
	Player();
	Player(int numb, char sign);
	virtual ~Player() {};

	int GetPlayerNumber() { return player_number; }
	char GetSign() { return player_sign; }

	virtual int Move(Board *b);
};

class Arbitrator {
	int number_of_players;
	int current_player;
	Player** players_array;
	Board* board;
public:
	Arbitrator(Board *b);
	~Arbitrator();

	void AddPlayer(Player* p);
	
	void Turn();
	void Run();
	
	int GetTurnNumber() { return current_player; }
	Player* GetPlayer() { return players_array[current_player - 1]; }
};

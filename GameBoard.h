#include <array>
#include <string>
#include <stdlib.h>
#include <set>
#include <time.h>
#include "Player.h"
#include "Opponent.h"


#ifndef GAMEBOARD_H_
#define GAMEBOARD_H_
using std::array;
using std::string;
class GameBoard
{
private:
	//array<char, 10> board;
	char board[10] = { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' };
	string vertDiv = { " | " };
	string horDiv = { "--- --- ---" };
	Player *player;		//keeps track of whos turn it is
	int pCount = 0;		//keeps track of number of players
	int count = 0;		//keeps track of number of moves;
	Player *p1;
	Player *p2;
public:
	GameBoard();
	void run_game();
	void display_board();
	bool check_winner(char m);
	int count_players();		//determines how many players
	void goes_first(int p);		//determines who goes first
	bool check_end_condition();
	void change_turn();
};

#endif

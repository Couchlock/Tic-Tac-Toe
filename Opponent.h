#include "Player.h"

#ifndef OPPONENT_H_
#define OPPONENT_H_

class Opponent : public Player
{
public:
	Opponent(char mark);
	int move(std::set<int> *a, Player *p, char *gb);
	int enemy_logic(Player *p, char *gb);
};

#endif

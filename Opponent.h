#include "Player.h"
#include <stack>

#ifndef OPPONENT_H_
#define OPPONENT_H_

class Opponent : public Player
{
private:
	int *count;
	const char Empty = ' ';
public:
	Opponent(char mark, int *c);
	int move(std::set<int> &a, Player *p, const char *gb);
	int enemy_logic(Player *p, const char *gb);
	bool check_even(const char *gb[]);
};

#endif

#include <string>
#include <set>

#ifndef PLAYER_H_
#define PLAYER_H_
class Player
{
private:
	char marker;
public:
	Player();
	Player(char mark);
	char get_marker();
	virtual int move(std::set<int> &a, Player *p, const char *gb);
	bool check_space(const int s, std::set<int> &a);
};

#endif
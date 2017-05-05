#include "Player.h"
#include "GameBoard.h"
#include <iostream>
#include <algorithm>

Player::Player()
{}

Player::Player(char mark)
{
	marker = mark;
}

char Player::get_marker()
{
	return marker;
}

int Player::move(std::set<int> &a, Player *p, const char *gb)
{
	std::cout << "Please choose a space: ";
	while (true)
	{
		int temp;
		std::cin >> temp;
		if (check_space(temp, a))
		{
			return temp;
		}
		else
			std::cout << "That space is taken, please choose another: ";
	}
}

bool Player::check_space(const int s, std::set<int> &a)
{
	std::set<int>::iterator it = a.find(s);
	if (it != a.end())
	{
		a.erase(it);
		return true;
	}
	else
		return false;
}
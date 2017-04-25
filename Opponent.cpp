#include "Opponent.h"
#include <iostream>
#include <time.h>

Opponent::Opponent(char mark)
	: Player(mark)
{
	std::cout << "new Opponent created\n";
}

int Opponent::move(std::set<int> *a, Player *p, char *gb)
{
	std::cout << "My Turn...\n";
	int temp = enemy_logic(p, gb);
	std::cout << "Temp: " << temp << std::endl;
	if (temp)
		return temp;
	std::set<int>::iterator it = a->begin();
	temp = rand() % a->size() + 1;	//random roll from within whats left of the set
	for (int i = 0; i < temp; i++, it++);	//match our iterator to position of our random roll
	it--;	//went one too far in for loop
	temp = *it;	//because i can't dereference this as a return value for some reason...
	a->erase(it);	//remove the selected space from pool of available spaces
	return temp;	//return the space computer selected
}

int Opponent::enemy_logic(Player *p, char *gb)
{
	char m = get_marker();
	while (true)
	{
		if ((gb[5] == m && gb[1] == m) || (gb[3] == m && gb[6] == m) || (gb[7] == m && gb[8] == m))
			if (gb[9] == ' ')
				return 9;
		if ((gb[5] == m && gb[2] == m) || (gb[7] == m && gb[9] == m))
			if (gb[8] == ' ')
				return 8;
		if ((gb[5] == m && gb[3] == m) || (gb[1] == m && gb[4] == m) || (gb[8] == m && gb[9] == m))
			if (gb[7] == ' ')
				return 7;
		if ((gb[5] == m && gb[4] == m) || (gb[3] == m && gb[9] == m))
			if (gb[6] == ' ')
				return 6;
		if ((gb[1] == m && gb[9] == m) || (gb[7] == m && gb[3] == m) || (gb[6] == m && gb[4] == m) || (gb[8] == m && gb[2] == m))
			if (gb[5] == ' ')
				return 5;
		if ((gb[5] == m && gb[6] == m) || (gb[1] == m && gb[7] == m))
			if (gb[4] == ' ')
				return 4;
		if ((gb[5] == m && gb[7] == m) || (gb[1] == m && gb[2] == m) || (gb[6] == m && gb[9] == m))
			if (gb[3] == ' ')
				return 3;
		if ((gb[5] == m && gb[8] == m) || (gb[1] == m && gb[3] == m))
			if (gb[2] == ' ')
				return 2;
		if ((gb[5] == m && gb[9] == m) || (gb[3] == m && gb[2] == m) || (gb[7] == m && gb[4] == m))
			if (gb[1] == ' ')
				return 1;
		if (m == get_marker())
		{
			m = p->get_marker();
			continue;
		}
		return 0;
	}
}
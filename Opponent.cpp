#include "Opponent.h"
#include <iostream>
#include <time.h>


Opponent::Opponent(char mark, int *c)
	: Player(mark)
{
	count = c;
	std::cout << "new Opponent created\n";
}

int Opponent::move(std::set<int> &a, Player *p, const char *gb)
{
	std::cout << "My Turn...\n";
	int temp = enemy_logic(p, gb);
	if (temp)
		return temp;
	std::set<int>::iterator it = a.begin();
	temp = rand() % a.size() + 1;	//random roll from within whats left of the set
	for (int i = 0; i < temp; i++, it++);	//match our iterator to position of our random roll
	it--;	//went one too far in for loop
	temp = *it;	//because i can't dereference this as a return value for some reason...
	a.erase(it);	//remove the selected space from pool of available spaces
	return temp;	//return the space computer selected
}

int Opponent::enemy_logic(Player *p, const char *gb)
{
	srand(time(NULL));
	static std::stack<int> lastMove;
	static char Case;
	static int intCase = 0;
	static int track;		//keep track of opponents first move
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
		else if (m == p->get_marker())
		{
			int temp;
			if (*count == 0)	//if its the very first move of the game
			{
				temp = rand() % 5 + 1;
				Case = temp == 5 ? 'B' : 'A';
			}
			switch (Case) {
			case('A'):
				switch (intCase) {
				case(0):
					if (*count == 0)						//if its the very first move...
					{
						temp = (temp == 1 ? 1 : temp == 2 ? 3 : temp == 3 ? 7 : 9);
						lastMove.push(temp);				//store temp as our last move...
						return temp;						//and return our space to move to.
					}
					if (*count == 2)						//if its our 2nd move and we went first
					{
						intCase = (10 - lastMove.top()) != Empty ? 1 : check_even(&gb);	//if 2nd player took our opposite corner move to case A1, otherwise continue with A0
						//intCase = check_even(&gb);									//check if 2nd player chose an even space...
						if (intCase != 1)		//check our current subCase, if its 1, rerun function loop
							return (10 - lastMove.top());	//otherwise, return the space opposite corner of our first move
					}
					if (*count == 4)						//if its our 3rd move and we went first...
					{
						if (lastMove.top() == 1 || lastMove.top() == 9)//if our first move was 1/9...(corners)
						{
							if (gb[3] == Empty && gb[7] == Empty)		//if either 3/7 is available...
								return ((rand() % 2 + 1) == 1 ? 3 : 7);	//return a random selection of 3/7
							else
								return (gb[3] == Empty ? 3 : 7);	//...otherwise return whichever one is empty
						}
						else if (lastMove.top() == 3 || lastMove.top() == 7)//same as last check but for spaces 3/7
						{
							if (gb[1] == Empty && gb[9] == Empty)
								return ((rand() % 2 + 1) == 1 ? 1 : 9);
							else
								return (gb[1] == Empty ? 1 : 9);
						}
					}
					//at this point if we went first and we made it through move 4 above, we will win on basic checks
				case(1):
					std::cout << "using case A1\n";
					if (*count == 2)		//if its our second move and we went first..
					{
						for (int i = 0; i <= 9; i++)
							if (gb[i] == p->get_marker())	//iterate through board to find which space
							{								//opponent chose
								track = i;					//store that space in track
								break;
							}
						return 5;	//return 5 but don't add 5 to lastMove!
					}
					if (*count == 4)	//if its our 3rd move and we went first
					{	//here we're creating a fork by not working adjacent to opponents last move based on our first move
						if (lastMove.top() == 1)	
							return (track != 2 ? 3 : 7);
						if (lastMove.top() == 3)
							return (track != 2 ? 1 : 9);
						if (lastMove.top() == 7)
							return (track != 4 ? 1 : 9);
						if (lastMove.top() == 9)
							return (track != 6 ? 3 : 7);
					}
					// only basic checks after this...we probably won at this point
				}
			case('B'):
				switch (intCase) {
				case(0):
					if (*count == 0)	//our first move and we go first
						return 5;
					if (*count == 2)	//our second move and we go first
					{
						for (int i = 0; i <= 9; i++)
							if (gb[i] == p->get_marker())	//get opponents first move
							{
								track = i;					//assign it to track
								break;
							}
						if (track % 2 == 0)	//if opponent chose an even space..
							return (track < 5 ? (track + 5) : (track - 5));	//this ensures opponents next move will be adjacent to their first move or they lose
						else//otherwise choose an even space to block any forks..
						{
							int temp = rand() % 4 + 1;
							return (temp == 1 ? 2 : temp == 2 ? 4 : temp == 3 ? 6 : 8);
						}
					}
				}
			}
		}
		return 0;	//base case to return random space
	}
}

bool Opponent::check_even(const char *gb[])
{
	for (int i = 2; i <= 8; i += 2)		//check if 2nd player chose an even space
		if ((*gb)[i] != Empty)				//if they did...
			return true;
	return false;
}
#include "GameBoard.h"
#include <iostream>
#include <set>
#include <vector>
int main()
{
	int *count = new int(0);
	GameBoard* gb = new GameBoard(count);
	gb->run_game();
	system("PAUSE");
}
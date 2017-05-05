#include "GameBoard.h"
#include <iostream>

using std::cout;
using std::endl;

GameBoard::GameBoard(){}

void GameBoard::run_game()
{
	while (true)
	{
		std::set<int> avail = { 1,2,3,4,5,6,7,8,9 };	//this reps the available set of spaces
		goes_first(count_players());
		while (!check_end_condition())
		{
			display_board();
			board[player->move(avail, p1, board)] = player->get_marker();
			if (check_winner(player->get_marker()))
				break;
			count++;
			change_turn();
		}
		break;	//to be replaced with the ability to play game again
	}
}

void GameBoard::display_board()	//displays the playing board in console
{
	cout << endl;
	for (int i = 7; i <= 9; i++)
	{
		if (i == 7 || i == 4 || i == 1)
			cout << " ";
		cout << board[i];
		if (i % 3 != 0)
			cout << vertDiv;
		if (i % 3 == 0 && i > 3)
			cout << endl << horDiv << endl;
		if (i == 9 || i == 6)
			i -= 6;
		else if (i == 3)
			break;
	}
	cout << "\n\n";
}
bool GameBoard::check_winner(char m)	//checks for tictactoe
{
	if ((board[5] == m && ((board[1] == m && board[9] == m) || (board[3] == m && board[7] == m) || (board[4] == m && board[6] == m) || (board[2] == m && board[8] == m))) ||
		(board[1] == m && ((board[2] == m && board[3] == m) || (board[4] == m && board[7] == m))) ||
		(board[9] == m && ((board[8] == m && board[7] == m) || (board[6] == m && board[3] == m))))
	{
		display_board();
		cout << player->get_marker() << " WINS!\n";
		return true;
	}
	return false;
}

int GameBoard::count_players()	//determines number of players
{
	while (true)
	{
		cout << "How many Players? ";
		std::cin >> pCount;
		if (pCount != 1 && pCount != 2)
			continue;
		else break;
	}
	p1 = new Player('X');
	if (pCount == 1)
		p2 = new Opponent('O');
	else
		p2 = new Player('O');
	return pCount;
}

void GameBoard::goes_first(int p)	//determines who goes first, randomly
{
	srand((unsigned int)time(NULL));
	int roll = rand() % 2 + 1;
	if (roll == 1)
	{
		player = p1;
		cout << p1->get_marker();
	}
	else
	{
		player = p2;
		cout << p2->get_marker();
	}
	cout << " goes first!\n";
}

void GameBoard::change_turn()	//changes active player
{
	if (player == p1)
		player = p2;
	else player = p1;
}

bool GameBoard::check_end_condition()	//checks for a tie
{
	if (count == 9)
	{
		display_board();
		cout << "It's a tie!\n";
		return true;
	}
	return false;
}
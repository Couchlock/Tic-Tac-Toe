//TicTacToe.cpp

/*
Requires:
variables, data types, and numerical operators
basic input/output
logic (if statements, switch statements)
loops (for, while, do-while)
arrays

Make a two player tic tac toe game.

Modify the program so that it will announce when a player has won the game (and which player won, x or o)

Modify the program so that it is a one player game against the computer (with the computer making its moves randomly)

Modify the program so that anytime the player is about to win (aka, they have 2 of 3 x's in a row, the computer will block w/ an o)

*/

#include <iostream>
#include <ctime>
#include <string>
#include <cctype>
#include <iomanip>
using std::string;

char board[3][3];
bool (*p)[3][3], p1[3][3], p2[3][3];
char player1, player2;
int count = 1;

//functions
void ticTacToe();
void showBoard();
int newGame(int numPlayers);
void playGame(int turn, int numPlayers);
bool checkscore(bool player[3][3]);
int checkUrgent(bool player[3][3], bool all[3][3]);

int main()
{
	ticTacToe();
}

void ticTacToe()//calls game
{
	int numPlayers;
	std::cout << std::setw(55) << " TIC TAC TOE\n\n";
	//determine number of players
	std::cout << std::setw(62) << "<1> player or <2> players? ";
	std::cin >> numPlayers;
	//old
	//start new game
	int turn = newGame(numPlayers);
	//call actual game
	playGame(turn, numPlayers);
}

void showBoard()//display the gameboard
{
	std::cout
		<< std::setw(50) << "3  " << board[0][0] << " | " << board[0][1] << " | " << board[0][2] << " \n"
		<< std::setw(61) << "  --- --- ---\n"
		<< std::setw(50) << "2  " << board[1][0] << " | " << board[1][1] << " | " << board[1][2] << " \n"
		<< std::setw(61) << "  --- --- ---\n"
		<< std::setw(50) << "1  " << board[2][0] << " | " << board[2][1] << " | " << board[2][2] << " \n"
		<< std::setw(62) << "   1   2   3 \n\n";
}

int newGame(int numPlayers)
{
	for (int j = 0; j < 3; j++)//populate gameboard with '.' placeholders and false values
	{
		for (int i = 0; i < 3; i++)
		{
			board[j][i] = '.';
			p1[j][i] = false;
			p2[j][i] = false;
		}
	}
	
	//tutorial
	std::cout << "\n\nA quick tutorial:\n"
			<< "Enter the two digits that correspond to the column and row you want to select\n<the first digit should be the column and the second digit should be the row>\n\n\tHere's an example selection :"
			<< "\tI'll select space 13\n\n\n"
			<< std::setw(54) << "3  O | " << board[0][1] << " | " << board[0][2] << " \n"
			<< std::setw(61) << "  --- --- ---\n"
			<< std::setw(50) << "2  " << board[1][0] << " | " << board[1][1] << " | " << board[1][2] << " \n"
			<< std::setw(61) << "  --- --- ---\n"
			<< std::setw(50) << "1  " << board[2][0] << " | " << board[2][1] << " | " << board[2][2] << " \n"
			<< std::setw(62) << "   1   2   3 \n\n";
	//showBoard();

	string ready;
	if (1 == numPlayers)
		std::cout << "\n" << std::setw(60) << "Now...\n\n" << std::setw(70) << "You will be X's and I will be O's\n\n"
				 << std::setw(71) << "Press enter when you're ready to begin";
	std::cin.ignore();
	getline(std::cin, ready);
	while (!ready.empty())
		continue;

	//lets randomly choose who starts, X's or O's
	srand((unsigned int)time(NULL));
	int turn = rand() % 2 + 1;
	if (turn == 1)
	{
		player1 = 'X', player2 = 'O';
		if (numPlayers == 2)
			std::cout << "\n\n\n\n\n" << std::setw(55) << "X's go first!\n\n";
		else std::cout << "\n\n\n\n\n" << std::setw(55) << "You go first!\n\n";
	}
	else
	{
		player1 = 'O', player2 = 'X';
		if (numPlayers == 2)
			std::cout << "\n\n\n\n\n" << std::setw(55) << "\nO's go first!\n\n";
		else std::cout << "\n\n\n\n\n" << std::setw(55) << "I go first!\n\n";
	}
	
	return turn;
}

void playGame(int turn, int numPlayers)
{
	int space; //variable to represent each game space
	char marker;// this is the X or the O
	string ready;
	bool allMoves[3][3];

	for (int i = 0; i < 3; i++) //set urgent board to false
		for (int j = 0; j < 3; j++)
		allMoves[i][j] = false;

	while (count <= 9)//game ends in a tie
	{
		if (1 == turn)//assign X or O to this turn
			{
				marker = 'X';
				p = &p1;
				std::cout << std::setw(65) << "Please select a space: ";
				std::cin >> space;
			}
		else
		{
			marker = 'O';
			p = &p2;
			if (2 == numPlayers)
			{
				std::cout << "Please select a space: ";
				std::cin >> space;
			}
			else
			{
				//checkUrgent(p1, allMoves);
				if (checkUrgent(p1, allMoves) == 0)
				{
					srand((unsigned int)time(NULL));
					space = rand() % 9 + 1;
				}
				else space = checkUrgent(p1, allMoves);
					//std::cout << std::endl << space << std::endl;
			}
		}
				
		//places the marker in the selected space. If space is filled it tells the player the space is already taken
		switch (space)
		{
		case 7:
		case 13:
			if (board[0][0] == '.')
			{
				board[0][0] = marker;
				(*p)[0][0] = true;
				allMoves[0][0] = true;
				if (numPlayers == 2 || 1 == numPlayers && 1 == turn)
					std::cout << "\nYou placed an " << marker << "!\n\n";
				else if (numPlayers == 1 && turn == 2)
					std::cout << "\nI placed an " << marker << "!\n\n";
				break;
			}
			else
			{
				if (numPlayers == 2 || 1 == numPlayers && 1 == turn)
					std::cout << "\nThat space is already taken.\n\n";
				continue;
			}
		case 4:
		case 12:
			if (board[1][0] == '.')
			{
				board[1][0] = marker;
				(*p)[1][0] = true;
				allMoves[1][0] = true;
				if (numPlayers == 2 || 1 == numPlayers && 1 == turn)
					std::cout << "\nYou placed an " << marker << "!\n\n";
				else if (numPlayers == 1 && turn == 2)
					std::cout << "\nI placed an " << marker << "!\n\n";
				break;
			}
			else
			{
				if (numPlayers == 2 || 1 == numPlayers && 1 == turn)
					std::cout << "\nThat space is already taken.\n\n";
				continue;
			}
		case 1:
		case 11:
			if (board[2][0] == '.')
			{
				board[2][0] = marker;
				(*p)[2][0] = true;
				allMoves[2][0] = true;
				if (numPlayers == 2 || 1 == numPlayers && 1 == turn)
					std::cout << "\nYou placed an " << marker << "!\n\n";
				else if (numPlayers == 1 && turn == 2)
					std::cout << "\nI placed an " << marker << "!\n\n";
				break;
			}
			else
			{
				if (numPlayers == 2 || 1 == numPlayers && 1 == turn)
					std::cout << "\nThat space is already taken.\n\n";
				continue;
			}
		case 8:
		case 23:
			if (board[0][1] == '.')
			{
				board[0][1] = marker;
				(*p)[0][1] = true;
				allMoves[0][1] = true;
				if (numPlayers == 2 || 1 == numPlayers && 1 == turn)
					std::cout << "\nYou placed an " << marker << "!\n\n";
				else if (numPlayers == 1 && turn == 2)
					std::cout << "\nI placed an " << marker << "!\n\n";
				break;
			}
			else
			{
				if (numPlayers == 2 || 1 == numPlayers && 1 == turn)
					std::cout << "\nThat space is already taken.\n\n";
				continue;
			}
		case 5:
		case 22:
			if (board[1][1] == '.')
			{
				board[1][1] = marker;
				(*p)[1][1] = true;
				allMoves[1][1] = true;
				if(numPlayers == 2 || 1 == numPlayers && 1 == turn)
					std::cout << "\nYou placed an " << marker << "!\n\n";
				else if (numPlayers == 1 && turn == 2)
					std::cout << "\nI placed an " << marker << "!\n\n";
				break;
			}
			else
			{
				if (numPlayers == 2 || 1 == numPlayers && 1 == turn)
					std::cout << "\nThat space is already taken.\n\n";
				continue;
			}
		case 2:
		case 21:
			if (board[2][1] == '.')
			{
				board[2][1] = marker;
				(*p)[2][1] = true;
				allMoves[2][1] = true;
				if (numPlayers == 2 || 1 == numPlayers && 1 == turn)
					std::cout << "\nYou placed an " << marker << "!\n\n";
				else if (numPlayers == 1 && turn == 2)
					std::cout << "\nI placed an " << marker << "!\n\n";
				break;
			}
			else
			{
				if (numPlayers == 2 || 1 == numPlayers && 1 == turn)
					std::cout << "\nThat space is already taken.\n\n";
				continue;
			}
		case 9:
		case 33:
			if (board[0][2] == '.')
			{
				board[0][2] = marker;
				(*p)[0][2] = true;
				allMoves[0][2] = true;
				if (numPlayers == 2 || 1 == numPlayers && 1 == turn)
					std::cout << "\nYou placed an " << marker << "!\n\n";
				else if (numPlayers == 1 && turn == 2)
					std::cout << "\nI placed an " << marker << "!\n\n";
				break;
			}
			else
			{
				if (numPlayers == 2 || 1 == numPlayers && 1 == turn)
					std::cout << "\nThat space is already taken.\n\n";
				continue;
			}
		case 6:
		case 32:
			if (board[1][2] == '.')
			{
				board[1][2] = marker;
				(*p)[1][2] = true;
				allMoves[1][2] = true;
				if (numPlayers == 2 || 1 == numPlayers && 1 == turn)
					std::cout << "\nYou placed an " << marker << "!\n\n";
				else if (numPlayers == 1 && turn == 2)
					std::cout << "\nI placed an " << marker << "!\n\n";
				break;
			}
			else
			{
				if (numPlayers == 2 || 1 == numPlayers && 1 == turn)
					std::cout << "\nThat space is already taken.\n\n";
				continue;
			}
		case 3:
		case 31:
			if (board[2][2] == '.')
			{
				board[2][2] = marker;
				(*p)[2][2] = true;
				allMoves[2][2] = true;
				if (numPlayers == 2 || 1 == numPlayers && 1 == turn)
					std::cout << "\nYou placed an " << marker << "!\n\n";
				else if (numPlayers == 1 && turn == 2)
					std::cout << "\nI placed an " << marker << "!\n\n";
				break;
			}
			else
			{
				if (numPlayers == 2 || 1 == numPlayers && 1 == turn)
					std::cout << "\nThat space is already taken.\n\n";
				continue;
			}
		}
		
		showBoard();

		if (checkscore(*p))
			break;

		if (1 == turn)
		{
			turn = 2;
		}
		else if (2 == turn)
			turn = 1;
		++count;
	}
	if (!(checkscore(*p)))
		std::cout << "\n\nTie Game!\n\n";
	else
		std::cout << std::endl << marker << " wins!\n\n";
	std::cout << "Press enter to exit.\n";
	std::cin.ignore();
	getline(std::cin, ready);
	while (!ready.empty())
		continue;
}

bool checkscore(bool player[3][3])
{
	bool win = false;
	if ((player[0][0] == true && player[0][1] == true && player[0][2] == true) || (player[1][0] == true && player[1][1] == true && player[1][2] == true) || (player[2][0] == true && player[2][1] == true && player[2][2] == true))
		win = true;
	if ((player[0][0] == true && player[1][0] == true && player[2][0] == true) || (player[0][1] == true && player[1][1] == true && player[2][1] == true) || (player[0][2] == true && player[1][2] == true && player[2][2] == true))
		win = true;
	if ((player[0][0] == true && player[1][1] == true && player[2][2] == true) || (player[2][0] == true && player[1][1] == true && player[0][2] == true))
		win = true;
	return win;
}

int checkUrgent(bool player[3][3], bool all[3][3])
{
	int urgent = 0;
	if ((all[0][0] == false && player[0][1] == true && player[0][2] == true) || (all[0][0] == false && player [1][1] == true && player [2][2] ==true) || (all[0][0] == false && player[1][0] == true && player[2][0] == true))
		urgent = 7;
	if ((player[0][0] == true && all[0][1] == false && player[0][2] == true) || (all[0][1] == false && player[1][1] == true && player[2][1] == true))
		urgent = 8;
	if ((player[0][0] == true && player[0][1] == true && all[0][2] == false) || (player[2][0] == true && player[1][1] == true && all[0][2] == false) || (all[0][2] == false && player[1][2] == true && player[2][2] == true))
		urgent = 9;
	if ((all[1][0] == false && player[1][1] == true && player[1][2] == true) || (player[0][0] == true && all[1][0] == false && player[2][0] == true))
		urgent = 4;
	if ((player[1][0] == true && all[1][1] == false && player[1][2] == true) || (player[0][1] == true && all[1][1] == false && player[2][1] == true) || (player[0][0] == true && all[1][1] == false && player [2][2] == true) || (player[0][2] == true && all[1][1] == false && player[2][0] == true))
		urgent = 5;
	if ((player[1][0] == true && player[1][1] == true && all[1][2] == false) || (player[0][2] == true && all[1][2] == false && player[2][2] == true))
		urgent = 6;
	if ((all[2][0] == false && player[2][1] == true && player[2][2] == true) || (player[0][0] == true && player[1][0] == true && all[2][0] == false) || (all[2][0] == false && player[1][1] == true && player[0][2] == true))
		urgent = 1;
	if ((player[2][0] == true && all[2][1] == false && player[2][2] == true) || (player[0][1] == true && player[1][1] == true && all[2][1] == false))
		urgent = 2;
	if ((player[2][0] == true && player[2][1] == true && all[2][2] == false) || (player[0][2] == true && player[1][2] == true && all[2][2] == false) || (player[0][0] == true && player[1][1] == true && all[2][2] == false))
		urgent = 3;

	return urgent;
}


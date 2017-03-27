#include <iostream>
#include <string>
#include <time.h>
#include <stdlib.h>

using namespace std;

const int SIZE = 10;
const char O = 'O', X = 'X';

struct Player
{
	std::string name;
	char marker = O;
	static unsigned int moves;
	int wins = 0;
	bool isPerson = true;
};

string gameBoard = { "          " };		//1-9 are our spaces
string vert_divide = { "--- --- ---" };
string hor_divide = { " | " };
bool boolBoard[10] = { false };				//1-9 are our spaces
char marker;
unsigned int space;
unsigned int moveCount = 0;
void display_gameBoard();
int get_players();
void assign_players(Player* p1, Player* p2);
void make_move(Player* p, unsigned int& count);
void set_boolBoard();
int check_urgent(string& gb, char& marker);
bool check_winner(std::string& gb, Player* p, unsigned int& count);
bool run_game(Player* p1, Player* p2);


int main()
{
	Player* p1 = new Player;
	Player* p2 = new Player;
	while (run_game(p1, p2));
	system("PAUSE");
	EXIT_SUCCESS;
}

bool run_game(Player* p1, Player* p2)
{
	assign_players(p1, p2);
	Player* player = p1;
	while (!(check_winner(gameBoard, p1, moveCount) || check_winner(gameBoard, p2, moveCount)))
	{
		make_move(player, moveCount);
		if (player == p1)
			player = p2;
		else player = p1;
	}
	std::cout << "Would you like to play again? (y)es or (n) ";
	char play;
	std::cin >> play;
	if (play == 'y')
	{
		gameBoard = { "          " };
		moveCount = 0;
		return true;
	}
	return false;
}
void display_gameBoard()	//verified
{	
	cout << endl;
	cout << " " << gameBoard[7] << hor_divide << gameBoard[8] << hor_divide << gameBoard[9] << " ";
	cout << endl;
	cout << vert_divide;
	cout << endl;
	cout << " " << gameBoard[4] << hor_divide << gameBoard[5] << hor_divide << gameBoard[6] << " ";
	cout << endl;
	cout << vert_divide << endl;
	cout << " " << gameBoard[1] << hor_divide << gameBoard[2] << hor_divide << gameBoard[3] << " ";
	cout << endl << endl;
}

void set_boolBoard()	//verified
{
	for (int i = 1; i < SIZE; i++)
	{
		if (gameBoard[i] == X || gameBoard[i] == O)
		{
			boolBoard[i] = true;
		}
	}
}

int get_players()
{
	cout << "How many Players?" << endl << "(1) or (2) or (q) to quit: ";
	unsigned int players = 0;
	if (cin >> players)
	{
		if (players == 1) return 1;
		else if (players == 2) return 2;
	}
	return 0;	
}

void assign_players(Player* p1, Player* p2)
{
	srand((unsigned int)time(NULL));
	int num = get_players();
	p1->marker = X;
	p2->marker = O;
	
	std::cout << "Here is your game board, each number corresponds to its respective space\n"
		<<"Enter the space number you would like and press Enter\n";
	gameBoard = { " 123456789" };
	display_gameBoard();
	gameBoard = { "          " };
	time_t start, current, seconds = 3;
	time(&start);
	do
	{
		time(&current);
	} while ((current - start) < seconds);
	if (num == 1)
	{
		if (rand() % 2 == 0)
		{
			p2->isPerson = false;
			std::cout << "You go first!\nYou will be " << p1->marker << "'s and I will be " << p2->marker << "'s\n";
		}
		else
		{
			p1->isPerson = false;
			std::cout << "I go first!\n";
			std::cout << "I will be " << p1->marker << "'s and you will be " << p2->marker << "'s\n";
		}	
	}
	else if (num == 2)
		std::cout << p1->marker << "'s go first!\n";
}

void make_move(Player* p, unsigned int& count)
{
	if (p->isPerson)
		display_gameBoard();
	if (p->isPerson == true)
	{
		std::cout << "Please select a space: ";
		unsigned int space;
		std::cin >> space;
		while (true)
		{
			if (space <= 0 || space > 9)
			{
				std::cout << "That is not a valid selection, please select another space:";
				cin.clear();
				while (cin.get() == '\n')
					continue;
				cin >> space;
				continue;
			}
			else if (gameBoard[space] == ' ')
			{
				gameBoard[space] = p->marker;
				count += 1;
				break;
			}
			else
			{
				std::cout << "That space is already taken, please select another: ";
				cin >> space;
				continue;
			}
		}
	}
	else
	{
		std::cout << "My turn:\n";
		while (true)
		{
			char temp = p->marker;
			unsigned int space = check_urgent(gameBoard, p->marker);
			if (space == 0)
			{
				if (p->marker == X)
					temp = O;
				else
					temp = X;
			}
			space = check_urgent(gameBoard, temp);
			if (space == 0)
			{
				srand((unsigned int)time(NULL));
				space = rand() % 9 + 1;
			}
			if (gameBoard[space] == ' ')
			{
				gameBoard[space] = p->marker;
				count += 1;
				break;
			}
			else
				continue;
		}
	}
	
}

bool check_winner(std::string& gb, Player* p, unsigned int& count)
{
	char m = p->marker;
	if ((gb[1] == m && gb[2] == m && gb[3] == m) || (gb[4] == m && gb[5] == m && gb[6] == m) ||
		(gb[7] == m && gb[8] == m && gb[9] == m) || (gb[1] == m && gb[4] == m && gb[7] == m) ||
		(gb[2] == m && gb[5] == m && gb[8] == m) || (gb[3] == m && gb[6] == m && gb[9] == m) ||
		(gb[1] == m && gb[5] == m && gb[9] == m) || (gb[3] == m && gb[5] == m && gb[7] == m))
	{
		display_gameBoard();
		std::cout << p->marker << "'s win!\n";
		return true;
	}
	else if (count >= 9)
	{
		display_gameBoard();
		std::cout << "It's a tie!\n";
		return true;
	}
	return false;
}

int check_urgent(string& gb, char& m)	//here m should be the previous players marker
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
	return 0;
}
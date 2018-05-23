#pragma once
#ifndef BOARD_H
#define BOARD_H
#include <cstdlib>
#include <ctime>
#include <iostream>>
#include <iomanip>
using namespace std;

const int boardSize = 5;
const double trial = 2550;
const int minValue = 0;
const int maxValue = 4;


class Board
{
private:
	int board[boardSize][boardSize];
	int innerBoard[boardSize][boardSize];
	double probability[boardSize][boardSize];
	int player = 1;
	int innerPlayer = 1;
	int count = 0;
	int LettertoCoordinates(char);
	void play(int, int);
	void randomPlay();
	int search_horizontal(int, int, int);
	int search_vertical(int, int, int);
	int search_slanting_leftToRight(int, int, int);
	int search_slanting_rightToLeft(int, int, int);
	int Innersearch_horizontal(int, int, int);
	int Innersearch_vertical(int, int, int);
	int Innersearch_slanting_leftToRight(int, int, int);
	int Innersearch_slanting_rightToLeft(int, int, int);
public:
	Board();
	void showBoard();
	void humanPlay();
	int winning();
	void copyInner();
	double playout(int ,int);
	int innerWinning();
	void comPlay();
	void showProbability();
	
};

Board::Board()
{
	for (int column = 0; column < boardSize; column++)
	{
		for (int row = 0; row < boardSize; row++)
		{
			board[column][row] = 0;
		}
	}
}

void Board::showBoard()
{
	cout << "   a b c d e f g h i j k l m n o" << endl;
	for (int column = 0; column < boardSize; column++)
	{
		cout << setw(2) << column + 1;
		cout << " ";
		for (int row = 0; row < boardSize; row++)
		{

			if (board[column][row] == 0)
				cout << "¥";
			else if (board[column][row] == 1)
				cout << "O";
			else if (board[column][row] == 2)
				cout << "X";
			cout << " ";
		}
		cout << endl;
	}
		
}

int Board::LettertoCoordinates(char letter)
{
	int row;
	if (letter == 'a')
		row = 0;
	else if (letter == 'b')
		row = 1;
	else if (letter == 'c')
		row = 2;
	else if (letter == 'd')
		row = 3;
	else if (letter == 'e')
		row = 4;
	else if (letter == 'f')
		row = 5;
	else if (letter == 'g')
		row = 6;
	else if (letter == 'h')
		row = 7;
	else if (letter == 'i')
		row = 8;
	else if (letter == 'j')
		row = 9;
	else if (letter == 'k')
		row = 10;
	else if (letter == 'l')
		row = 11;
	else if (letter == 'm')
		row = 12;
	else if (letter == 'n')
		row = 13;
	else if (letter == 'o')
		row = 14;
	else
		row = -1;
	
	return row;
}


void Board::humanPlay()
{
	char letter;
	int column = 1, row = 1;
	do
	{
		if (player == 1)
		{
			if (row >= boardSize || row < 0 || column >= boardSize || column < 0)
				cout << "It's an illegal move" << endl;
			cout << "It's player1's turn." << endl
				<< "Please enter the hirizontal coordinate from 'a' to 'n' that you want to play" << endl;
			cin >> letter;
			cout << "Please enter the vertical coordinate from 1 to 15 that you want to play" << endl;
			cin >> column;
		}
		else if (player == 2)
		{
			if (row > boardSize || row < 0 || column > boardSize || column < 0)
				cout << "Is's an illegal move" << endl;
			cout << "It's player2's turn." << endl
				<< "Please enter the hirizontal coordinate from 'a' to 'n' that you want to play" << endl;
			cin >> letter;
			cout << "Please enter the vertical coordinate from 1 to 15 that you want to play" << endl;
			cin >> column;
		}

		row = LettertoCoordinates(letter);
	} while (row > boardSize || row < 0 || column > boardSize || column < 0);
	play(column - 1, row );
}

void Board::play(int column, int row)
{
	if (player == 1)
	{
		board[column][row] = 1;
		player = 2;
	}
	else
	{
		board[column][row] = 2;
		player = 1;
	}
}

int Board::search_horizontal(int column, int row, int piece)
{

	if (board[column][row] != piece)
	{
		if (count >= 5)
		{
			count = 0;
			return piece;
		}
		else
		{
			count = 0;
			return 0;
		}
	}
	else if (board[column][row] == piece) // This recoursively works as long as the position has a given peices.
	{
		count++;
		search_horizontal(column, row + 1, piece);
	}
}

int Board::search_vertical(int column, int row, int piece)
{
	if (board[column][row] != piece)
	{
		if (count >= 5)
		{
			count = 0;
			return piece;
		}
		else
		{
			count = 0;
			return 0;
		}
	}
	else if (board[column][row] == piece) // same as above
	{
		count++;
		search_vertical(column + 1, row, piece);
	}
}

int Board::search_slanting_leftToRight(int column, int row, int piece)
{
	if (board[column][row] != piece)
	{
		if (count >= 5)
		{
			count = 0;
			return piece;
		}
		else
		{
			count = 0;
			return 0;
		}
	}
	else if (board[column][row] == piece)//same as avobe
	{
		count++;
		search_slanting_leftToRight(column + 1, row + 1, piece);
	}
}

int Board::search_slanting_rightToLeft(int column, int row, int piece)
{
	if (board[column][row] != piece)
	{
		if (count >= 5)
		{
			count = 0;
			return piece;
		}
		else
		{
			count = 0;
			return 0;
		}
	}
	else if (board[column][row] == piece)//same as avobe
	{
		count++;
		search_slanting_rightToLeft(column - 1, row - 1, piece);
	}
}

int Board::winning()
{
	int winning = 0;
	for (int column = 0; column < boardSize; column++)
	{
		for (int row = 0; row < boardSize - 4; row++)// no need to see the four positions on the right side.
		{
			if (board[column][row] == 1)
			{
				winning = search_horizontal(column, row, 1);
				if (winning == 1)
					return winning;
			}
			else if (board[column][row] == 2)
			{
				winning = search_horizontal(column, row, 2);
				if (winning == 2)
					return winning;
			}
				
		}
	}

	for (int row = 0; row < boardSize; row++)
	{
		for (int column = 0; column < boardSize - 4; column++)
		{
			if (board[column][row] == 1)
			{
				winning = search_vertical(column, row, 1);
				if (winning == 1)
					return winning;
			}
			else if (board[column][row] == 2)
			{
				winning = search_vertical(column, row, 2);
				if (winning == 2)
					return winning;
			}
				
		}
	}

	for (int column = 0; column < boardSize - 4; column++)
	{
		for (int row = 0; row < boardSize - 4; row++)//from upper left to lower right
		{
			if (board[column][row] == 1)
			{
				winning = search_slanting_leftToRight(column, row, 1);
				if (winning == 1)
					return winning;
			}
			else if (board[column][row] == 2)
			{
				winning = search_slanting_leftToRight(column, row, 2);
				if (winning == 2)
					return winning;
			}
				
		}
		for (int row = 14; row > 4; row--)//from upper right to lower left
		{
			if (board[column][row] == 1)
			{
				winning = search_slanting_rightToLeft(column, row, 1);
				if (winning == 1)
					return winning;
			}
			else if (board[column][row] == 2)
			{
				winning = search_slanting_rightToLeft(column, row, 2);
				if (winning == 2)
					return winning;
			}
				
		}
	}

	if (winning == 0)
	{
		int draw = true;
		for (int x = 0; x < boardSize; x++)
		{
			for (int y = 0; y < boardSize; y++)
			{
				if (board[x][y] == 0)
					draw = false;
			}
		}

		if (draw)
			return 3;
		else
			return 0;
	}
}

int Board::Innersearch_horizontal(int column, int row, int piece)
{

	if (innerBoard[column][row] != piece)
	{
		if (count >= 5)
		{
			count = 0;
			return piece;
		}
		else
		{
			count = 0;
			return 0;
		}
	}
	else if (innerBoard[column][row] == piece) // This recoursively works as long as the position has a given peices.
	{
		count++;
		Innersearch_horizontal(column, row + 1, piece);
	}
}

int Board::Innersearch_vertical(int column, int row, int piece)
{
	if (innerBoard[column][row] != piece)
	{
		if (count >= 5)
		{
			count = 0;
			return piece;
		}
		else
		{
			count = 0;
			return 0;
		}
	}
	else if (innerBoard[column][row] == piece) // same as above
	{
		count++;
		Innersearch_vertical(column + 1, row, piece);
	}
}

int Board::Innersearch_slanting_leftToRight(int column, int row, int piece)
{
	if (innerBoard[column][row] != piece)
	{
		if (count >= 5)
		{
			count = 0;
			return piece;
		}
		else
		{
			count = 0;
			return 0;
		}
	}
	else if (innerBoard[column][row] == piece)//same as avobe
	{
		count++;
		Innersearch_slanting_leftToRight(column + 1, row + 1, piece);
	}
}

int Board::Innersearch_slanting_rightToLeft(int column, int row, int piece)
{
	if (innerBoard[column][row] != piece)
	{
		if (count >= 5)
		{
			count = 0;
			return piece;
		}
		else
		{
			count = 0;
			return 0;
		}
	}
	else if (innerBoard[column][row] == piece)//same as avobe
	{
		count++;
		Innersearch_slanting_rightToLeft(column - 1, row - 1, piece);
	}
}

int Board::innerWinning()
{
	int winning = 0;
	for (int column = 0; column < boardSize; column++)
	{
		for (int row = 0; row < boardSize - 4; row++)// no need to see the four positions on the right side.
		{
			if (innerBoard[column][row] == 1)
			{
				winning = Innersearch_horizontal(column, row, 1);
				if (winning == 1)
					return winning;
			}
			else if (innerBoard[column][row] == 2)
			{
				winning = Innersearch_horizontal(column, row, 2);
				if (winning == 2)
					return winning;
			}
				
		}
	}

	for (int row = 0; row < boardSize; row++)
	{
		for (int column = 0; column < boardSize - 4; column++)
		{
			if (innerBoard[column][row] == 1)
			{
				winning = Innersearch_vertical(column, row, 1);
				if (winning == 1)
					return winning;
			}
			else if (innerBoard[column][row] == 2)
			{
				winning = Innersearch_vertical(column, row, 2);
				if (winning == 2)
					return winning;
			}
				
		}
	}

	for (int column = 0; column < boardSize - 4; column++)
	{
		for (int row = 0; row < boardSize - 4; row++)//from upper left to lower right
		{
			if (innerBoard[column][row] == 1)
			{
				winning = Innersearch_slanting_leftToRight(column, row, 1);
				if (winning == 1)
					return 1;
			}
			else if (innerBoard[column][row] == 2)
			{
				winning = Innersearch_slanting_leftToRight(column, row, 2);
				if (winning == 2)
					return winning;
			}
				
		}
		for (int row = 4; row > 4; row--)//from upper right to lower left
		{
			if (innerBoard[column][row] == 1)
			{
				winning = Innersearch_slanting_rightToLeft(column, row, 1);
				if (winning == 1)
					return winning;
			}
			else if (innerBoard[column][row] == 2)
			{
				winning = Innersearch_slanting_rightToLeft(column, row, 2);
				if (winning == 2)
					return winning;
			}
				
		}
	}

	if (winning == 0)
	{
		int draw = true;
		for (int x = 0; x < boardSize; x++)
		{
			for (int y = 0; y < boardSize; y++)
			{
				if (innerBoard[x][y] == 0)
					draw = false;
			}
		}

		if (draw)
			return 3;
		else
			return 0;
	}
}

void Board::copyInner()
{
	for (int column = 0; column < boardSize; column++)
	{
		for (int row = 0; row < boardSize; row++)
		{
			innerBoard[column][row] = board[column][row];
		}
	}
	innerPlayer = player;
}
	
void Board::randomPlay()
{
	int x, y;
	unsigned seed = time(0);
	srand(seed);
	do
	{
		x = (rand() % (maxValue - minValue + 1)) + minValue;
		y = (rand() % (maxValue - minValue + 1)) + minValue;
	} while (innerBoard[x][y] != 0);

	if (innerPlayer == 1)
	{
		innerBoard[x][y] = 1;
		innerPlayer = 2;
	}
	else
	{
		innerBoard[x][y] = 2;
		innerPlayer = 1;
	}
}

double Board::playout(int x, int y)
{
	double win = 1, lose = 0, draw = 0.5;
	copyInner();
	if (innerPlayer == 1)
	{
		innerBoard[x][y] = 1;
		innerPlayer = 2;
	}
	else
	{
		innerBoard[x][y] = 2;
		innerPlayer = 1;
	}
	while(innerWinning() == 0)
		randomPlay();
	int winner = innerWinning();
	copyInner();
	if (winner == 1)
	{
		if (innerPlayer == 1)
			return win;
		else
			return lose;
	}
	else if (winner == 2)
	{
		if (innerPlayer == 1)
			return lose;
		else
			return win;
	}
	else if (winner == 3)
		return draw;
}

void Board::comPlay()
{
	for (int x = 0; x < boardSize; x++)
	{
		for (int y = 0; y < boardSize; y++)
		{
			if (board[x][y] == 1 || board[x][y] == 2)
				probability[x][y] = -1;
			else
			{
				probability[x][y] = 0;
				for (int i = 0; i < trial; i++)
					probability[x][y] = probability[x][y] + playout(x, y);

				probability[x][y] = probability[x][y] / trial;
			}
		}
	}
	int xPlay, yPlay;
	double tempProbability = -1;
	for (int x = 0; x < boardSize; x++)
	{
		for (int y = 0; y < boardSize; y++)
		{
			if (probability[x][y] > tempProbability)
			{
				tempProbability = probability[x][y];
				xPlay = x;
				yPlay = y;
			}
		}
	}
	play(xPlay, yPlay);
}

void Board::showProbability()
{
	for (int x = 0; x < boardSize; x++)
	{
		for (int y = 0; y < boardSize; y++)
		{
			cout << setw(4) << setprecision(2) << probability[x][y];
			cout << " ";
		}
		cout << endl;
	}
}


		








#endif // !BOARD_H


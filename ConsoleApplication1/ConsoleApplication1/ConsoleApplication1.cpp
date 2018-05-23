// ConsoleApplication1.cpp : アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"
#include "Board.h"
#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
	
	int countinue = 1;
	do
	{
		Board gomoku;
		cout << "This game is Gomoku" << endl;
		do
		{
			gomoku.showBoard();
			gomoku.humanPlay();
			gomoku.showBoard();
			gomoku.comPlay();
			gomoku.showProbability();
			
			
		} while (gomoku.winning() == 0);

		if (gomoku.winning() == 1)
			cout << "Player 1 won!" << endl;
		else if (gomoku.winning() == 2)
			cout << "Player 2 won!" << endl;
		else if (gomoku.winning() == 3)
			cout << "Draw!" << endl;

		cout << "Do you wnat to play again? 1 for yes 2 for no" << endl;
		cin >> countinue;
	}while(countinue == 1);
	

	return 0;
}


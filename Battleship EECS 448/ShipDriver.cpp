#include "ShipDriver.h"
#include <iostream>
using namespace std;

ShipDriver::ShipDriver()
{
	m_P1ShipNum = 0;
	m_P1ShipNum = 0;
	SetUpBoard();
}

void ShipDriver::SetUpBoard()
{
	do {
		std::cout << "Player 1, Please enter the number of ships you'd like to play with (1-6): ";
		std::cin >> m_P1ShipNum;;

		/*
		* Code courtesy of Doug T. at https://stackoverflow.com/questions/5864540/infinite-loop-with-cin-when-typing-string-while-a-number-is-expected
		*/
		if (cin.fail()) // If user has a bad input i.e. char 
		{
			cin.clear(); // get rid of failure state
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discards bad character
		}
	} while (m_P1ShipNum < 1 or m_P1ShipNum > 6);
	
	//Something with ShipBoard 1
	do {
		std::cout << "\nPlayer 2, Please enter the number of ships you'd like to play with (1-6): ";
		std::cin >> m_P2ShipNum;

		if (cin.fail()) 
		{
			cin.clear(); 
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
	} while (m_P2ShipNum < 1 or m_P2ShipNum > 6);

	//Something with ShipBoard 2
}

/*
void ShipDriver::StartGame()
{
	while(!checkWin())
	{
		int playerTurn = 1;
		switch(playerTurn)
		{
			case 1:
				//Player 1 turn stuff
			case 2:
				//Player 2 turn stuff
		}
	}
}*/

bool ShipDriver::CheckWin()
{
	return(false);
}

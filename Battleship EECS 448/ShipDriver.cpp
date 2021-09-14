#include "ShipDriver.h"

ShipDriver::ShipDriver()
{
	setUpBoard();
	startGame();
}

void ShipDriver::setUpBoard()
{
	int numOfShips;
	std::cout<<"Player 1, Please enter the number of ships you'd like to play with: ";
	std::cin>>numOfShips;
	//Something with ShipBoard 1
	std::cout<<"Player 2, Please enter the number of ships you'd like to play with: ";
	std::cin>>numOfShips;
	//Something with ShipBoard 2
}

void ShipDriver::startGame()
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
}

bool ShipDriver::checkWin()
{

}

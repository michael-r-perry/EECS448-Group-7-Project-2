#include <iostream>
#include "DisplayBoard.h"
#include "ShipBoard.h"
#include "ShipBoard.cpp"
using namespace std;

ShipBoard Ship;

void DisplayBoard::ShowBoard()
{
	std::cout << "  A B C D E F G H I J\n";
	int rowCounter = 1;
		for (int i = 0; i < rows; i++)
		{
			cout << rowCounter << " ";
			for (int j = 0; j < columns; j++)
			{
				std::cout << Ship.getBoardState(i,j) << " ";
			}
		std::cout << "\n";
		rowCounter += 1;
		}
}

void DisplayBoard::NumOfShipsPrompt()
{
	do {
		std::cout << "How many ships will be in play? (1-6)\n";
		std::cin >> shipNum;

		/*
		* Code courtesy of Doug T. at https://stackoverflow.com/questions/5864540/infinite-loop-with-cin-when-typing-string-while-a-number-is-expected
		*/
		if (cin.fail()) // If user has a bad input i.e. char 
		{
			cin.clear(); // get rid of failure state
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discards bad character
		}
	} while (shipNum < 1 or shipNum > 6);
	std::cout << "You chose " << shipNum << " ship(s)";
}

int DisplayBoard::NumOfShips()
{
	return(shipNum);
}

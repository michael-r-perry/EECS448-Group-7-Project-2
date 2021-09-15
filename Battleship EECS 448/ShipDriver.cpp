#include "ShipDriver.h"
#include "DisplayBoard.h"
#include <iostream>
using namespace std;

DisplayBoard display;

ShipDriver::ShipDriver()
{
	m_P1ShipNum = 0;
	m_P1ShipNum = 0;
	playerTurn = 1;
	SetUpBoard();
}

void ShipDriver::SetUpBoard()
{
	// Get Player 1's number of ships
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
	
	// Get Player 2's number of ships
	do {
		std::cout << "\nPlayer 2, Please enter the number of ships you'd like to play with (1-6): ";
		std::cin >> m_P2ShipNum;

		if (cin.fail()) 
		{
			cin.clear(); 
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
	} while (m_P2ShipNum < 1 or m_P2ShipNum > 6);

	PopulateBoard(m_P1ShipNum, m_P2ShipNum);
}

void ShipDriver::PopulateBoard(int m_P1ShipNum, int m_P2ShipNum)
{
	std::cout << endl;
	display.ShowBoard();
	int counter = 0; // Counter used to ensure all ships have been placed
	char input;
	string coordinate; 

	// Player 1:
	do
	{
		std::cout << "Please enter the orientation for your 1x" << counter + 1 << " ship (h = horizontal, v = vertical): ";
		std::cin >> input;
		input = tolower(input);
		if (input == 'h')
		{
			std::cout << "Please enter the coordinate you would like to place the ship (ex: A1): ";
			std::cin >> coordinate; 
			while (ConvertCoordinate(coordinate) == -1) // user input a bad coordinate
			{
				std::cout << "Please enter the coordinate you would like to place the ship (ex: A1): ";
				std::cin >> coordinate;
			}
		}

	} while ((counter < m_P1ShipNum) || (input != 'h') || (input != 'v'));


}

int ShipDriver::ConvertCoordinate(string coordinate)
{
	char col = coordinate.at(0);
	int row = coordinate.at(1);

	std::cout << "Column: " << col << endl;
	std::cout << "Row: " << row << endl; 

	return(1);
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
			case -1:
				//Player 2 turn stuff
		}
	}
}*/

bool ShipDriver::CheckWin()
{
	return(false);
}

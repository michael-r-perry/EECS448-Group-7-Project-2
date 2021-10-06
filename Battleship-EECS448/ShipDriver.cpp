#include "ShipDriver.h"
#include "DisplayBoard.h"
#include "ShipBoard.h"
#include "AI.h"
#include <iostream>
#include <tuple>
#include <stdlib.h>
#include <thread>
#include <chrono>
//#include <windows.h>
//#pragma comment(lib, "winmm.lib")
using namespace std;

ShipDriver::ShipDriver()
{
	m_ifAI = false;
	m_shipNum = 0;
	playerTurn = 1;
	counter = 0;
	SetUpBoard();
}

void ShipDriver::SetUpBoard()
{
	char gameType;
	char difficulty;
	do  // Get game type from user
	{
		cout << "1.) Play against another player\n"; // Display menu
		cout << "2.) Play against the AI\n";
		cout << "Enter choice: ";
		cin >> gameType;
	} while (gameType != '1' && gameType != '2');
	system("CLS");

	// if user chooses to play AI
	if (gameType == '2') // Get and set AI difficulty as well as change m_ifAI to true
	{
		m_ifAI = true;
		do 
		{
			cout << "Welcome to the AI section of SetUpBoard()!\n";
			cout << "Choose AI difficulty (E = Easy, M = Medium, H = Hard).\n";
			cout << "Enter choice: ";
			cin >> difficulty;
		} while ((difficulty != 'E' && difficulty != 'M') && difficulty != 'H');
		m_AI.setDifficulty(difficulty);
		system("CLS");
	}

	// Get the number of ships from the player
	do {
		std::cout << "Please enter the number of ships you'd like to play with (1-6): ";
		std::cin >> m_shipNum;;

		/*
		* Code courtesy of Doug T. at https://stackoverflow.com/questions/5864540/infinite-loop-with-cin-when-typing-string-while-a-number-is-expected
		*/
		if (cin.fail()) // If user has a bad input i.e. char 
		{
			cin.clear(); // get rid of failure state
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discards bad character
		}
	} while (m_shipNum < 1 or m_shipNum > 6);

	PopulateBoard(m_shipNum);
}

void ShipDriver::PopulateBoard(int m_shipNum)
{
	system("CLS");
	std::cout << endl;
	char input;
	string coordinate;
	int adjRow; // the adjusted row value after converting the user's coordinate
	int adjCol; // the adjusted column value after converting the user's coordinate

	// Player 1:
	if (playerTurn == 1)
	{
		while(counter < m_shipNum && playerTurn == 1)
		{
			system("CLS");
			display.ShowShips(m_P1);
			std::cout << "Player 1, Please enter the orientation for your 1x" << counter + 1 << " ship (h = horizontal, v = vertical): ";
			std::cin >> input;
			input = tolower(input); // converts answer to lowercase
			if (input == 'h')
			{
				std::cout << "Please enter the coordinate you would like to place the ship (ex: A1): ";
				std::cin >> coordinate;
				while (get<0>(ConvertCoordinate(coordinate)) == -1) // user input a bad coordinate. Gets first value of tuple. 
				{
					std::cout << "Please enter the coordinate you would like to place the ship (ex: A1): ";
					std::cin >> coordinate;
				}

				adjRow = get<0>(ConvertCoordinate(coordinate));
				adjCol = get<1>(ConvertCoordinate(coordinate));

				PlaceShip(adjRow, adjCol, input);
			}
			else if (input == 'v')
			{
				std::cout << "Please enter the coordinate you would like to place the ship (ex: A1): ";
				std::cin >> coordinate;
				while (get<0>(ConvertCoordinate(coordinate)) == -1) // user input a bad coordinate. Gets first value of tuple. 
				{
					std::cout << "Please enter the coordinate you would like to place the ship (ex: A1): ";
					std::cin >> coordinate;
				}

				adjRow = get<0>(ConvertCoordinate(coordinate));
				adjCol = get<1>(ConvertCoordinate(coordinate));

				PlaceShip(adjRow, adjCol, input);
			}
			else
			{
				std::cout << "Invalid input. Please try again.\n";
				if (cin.fail())
				{
					cin.clear();
					cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				}
			}
		}
	}

	// Player 2
	if (playerTurn == -1)
	{
		if (!m_ifAI)
		{
			while(counter < m_shipNum)
			{
				system("CLS");
				display.ShowShips(m_P2);
				std::cout << "Player 2, Please enter the orientation for your 1x" << counter + 1 << " ship (h = horizontal, v = vertical): ";
				std::cin >> input;
				input = tolower(input); // converts answer to lowercase
				if (input == 'h')
				{
					std::cout << "Please enter the coordinate you would like to place the ship (ex: A1): ";
					std::cin >> coordinate;
					while (get<0>(ConvertCoordinate(coordinate)) == -1) // user input a bad coordinate. Gets first value of tuple. 
					{
						std::cout << "Please enter the coordinate you would like to place the ship (ex: A1): ";
						std::cin >> coordinate;
					}

					adjRow = get<0>(ConvertCoordinate(coordinate));
					adjCol = get<1>(ConvertCoordinate(coordinate));

					PlaceShip(adjRow, adjCol, input);
				}
				else if (input == 'v')
				{
					std::cout << "Please enter the coordinate you would like to place the ship (ex: A1): ";
					std::cin >> coordinate;
					while (get<0>(ConvertCoordinate(coordinate)) == -1) // user input a bad coordinate. Gets first value of tuple. 
					{
						std::cout << "Please enter the coordinate you would like to place the ship (ex: A1): ";
						std::cin >> coordinate;
					}

					adjRow = get<0>(ConvertCoordinate(coordinate));
					adjCol = get<1>(ConvertCoordinate(coordinate));

					PlaceShip(adjRow, adjCol, input);
				}
				else
				{
					std::cout << "Invalid input. Please try again.\n";
					if (cin.fail())
					{
						cin.clear();
						cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					}
				}
			}
		}
		else // Place ships with AI
		{
			while(counter < m_shipNum)
			{
				system("CLS");
				display.ShowShips(m_P2);
				char rotation = m_AI.selectOrientation();
				std::tuple<int, int> coords = m_AI.placeShip(rotation, counter);
				std::cout << "Row,Col,Orietation,Counter: " << get<0>(coords) << ", " << get<1>(coords) << ", " << rotation << ", " << counter << std::endl;
				PlaceShip(get<0>(coords), get<1>(coords), rotation);
			}
		}
	}
	if (playerTurn == 0) // Runs once both players have placed their ships
	{
		display.ShowShips(m_P2); // shows player 2's final board state before starting the game
		std::cout << "Clearing the screen in 5 seconds. Switch players because the game is about to start!\n";
		ClearScreen();
		playerTurn = 1;
		StartGame();
	}
}

std::tuple<int, int> ShipDriver::ConvertCoordinate(string coordinate)
{
	/* When taking the int of a character, it is converted to its ASCII value equivalent. 
	* Therefore, col is subtracting 'a' from the coordinate position as this will cancel out the ASCII conversion and give us the correct column.
	* Row is done in a similar way, but 1 must be subtracted in order to account for the fact that there is no 0 coordinate on the board (from the player's POV)
	* Ex: Coordinate entered: B5
	* 'b' = 98, 'a' = 97. 98 - 97 = 1 -- the correct index location for B
	* '5' = 53, '0' = 48. 53 - 48 = 5 - 1 = 4 -- the correct index location for 5
	*/
	int row;
	int col;
	try
	{
		col = tolower(coordinate.at(0)) - 'a';
		row = coordinate.at(1) - '0' - 1; // only grabs the second index position of the string. Eliminates possibility of player typing "A1234"
	}
	catch (exception e)
	{
		row = -1; // sets row to -1 if user has bad input
		col = -1; // sets col to -1 if user has bad input
	}
	

	if ((col < 10) && (row < 9) && (col >= 0) && (row >= 0))
	{
		return make_tuple(row, col);
	}
	else
	{
		std::cout << "Invalid coordinate!\n";
		return make_tuple(-1, 0);
	}

}

void ShipDriver::PlaceShip(int row, int col, char rotation)
{
	//Goal: Use mark on ShipBoard to place the correct ship on the board
	//Use counter as size of ship in order to verify placement (i.e not going out of bounds)
	bool legalPlacement = true;
	if (playerTurn == 1)
	{
		if (counter >= 0 && counter <= 5)
		{
			if (counter != 0) // Ships of Size 1x1 are the first ship placed and don't need to be checked for legalPlacement or have rotation
			{
				for (int i = 0; i <= counter; i++) // checks all positions that the ship will occupy first before assigning ship to a coordinate
				{
					if (rotation == 'h') // adds i to col for horizontal placement
					{
						if (col + i > 9) { legalPlacement = false; break; } // quick out of bounds bug fix

						if (m_P1.GetTile(row, col + i) == '0')
						{
							legalPlacement = true;
						}
						else 
						{
							legalPlacement = false;
							break;
						}
					}
					else if (rotation == 'v') // subtracts i to row for vertical placement
					{
						if (row - i < 0) { legalPlacement = false; break; } // quick out of bounds bug fix

						if (m_P1.GetTile(row - i, col) == '0')
						{
							legalPlacement = true;
						}
						else 
						{
							legalPlacement = false;
							break;
						}
					}
				}
			}

			if (legalPlacement)
			{
				for (int i = 0; i <= counter; i++)
				{
					if (rotation == 'h')
					{
						m_P1.SetTile(row, col + i, 'S');
					}
					else 
					{
						m_P1.SetTile(row - i, col, 'S');
					}
				}
				counter++;
				if (counter == m_shipNum) // turns over control to player 2 after player 1 has placed all their ships
				{
					system("CLS");
					playerTurn = -1;
					counter = 0; // initializes counter back to zero for Player 2
					display.ShowShips(m_P1);
					std::cout << "Clearing the screen in 5 seconds. Switch players now...\n";
					ClearScreen();
				}
			}
			else
			{
				std::cout << "\nIllegal placement of ship\n";
				return;
			}
		}
	}
	else if (playerTurn == -1)
	{
		if (counter >= 0 && counter <= 5)
		{
			if (counter != 0) // Ships of Size 1x1 are the first ship placed and don't need to be checked for legalPlacement or have rotation
			{
				for (int i = 0; i <= counter; i++) // checks all positions that the ship will occupy first before assigning ship to a coordinate
				{
					if (rotation == 'h') // adds i to col for horizontal placement
					{
						if (col + i > 9) { legalPlacement = false; break; } // quick out of bounds bug fix

						if (m_P2.GetTile(row, col + i) == '0') 
						{
							legalPlacement = true;
						}
						else 
						{
							legalPlacement = false;
							break;
						}
					}
					else if (rotation == 'v') // subtracts i to row for vertical placement
					{
						if (row - i < 0) { legalPlacement = false; break; } // quick out of bounds bug fix

						if (m_P2.GetTile(row - i, col) == '0')
						{
							legalPlacement = true;
						}
						else 
						{
							legalPlacement = false;
							break;
						}
					}
				}
			}

			if (legalPlacement)
			{
				for (int i = 0; i <= counter; i++)
				{
					if (rotation == 'h')
					{
						m_P2.SetTile(row, col + i, 'S');
					}
					else 
					{
						m_P2.SetTile(row - i, col, 'S');
					}
				}
				counter++;
				if (counter == m_shipNum)
				{
					system("CLS");
					playerTurn = 0; // sets playerTurn to 0 to transition to StartGame();
				}
			}
			else
			{
				std::cout << "\nIllegal placement of ship\n";
				return;
			}
		}
	}
}
 
/*
void ShipDriver::PlaceShip(int row, int col, char rotation)
{
	//Goal: Use mark on ShipBoard to place the correct ship on the board
	//Use counter as size of ship in order to verify placement (i.e not going out of bounds)
	bool legalPlacement;
	if(playerTurn == 1)
	{
		//For a  ship of size 1 rotation does not matter
		if (counter == 0)
		{
			m_P1.SetTile(row, col, 'S');
			counter++;
			if (counter >= m_shipNum)
			{
				system("CLS");
				playerTurn = -1;
				counter = 0; // initializes counter back to zero for Player 2
				display.ShowShips(m_P1);
				std::cout << "Clearing the screen in 5 seconds. Switch players now...\n";
				ClearScreen();
			}
			return;
		}
		if(rotation == 'h') // adds i to col for horizontal placement
		{
			if (counter == 1)
			{
				for (int i = 0; i <= counter; i++)
				{
					std::cout << "Row,Col: " << row << "," << (col+i) << std::endl;
					if (m_P1.GetTile(row, col + i) == '0') // checks all positions that the ship will occupy first before assigning ship to a coordinate
					{
						legalPlacement = true;
					}
					else
					{
						std::cout << "\nIllegal placement of ship\n";
						legalPlacement = false;
						break;
					}
				}
				if (legalPlacement)
				{
					m_P1.SetTile(row, col, 'S');
					m_P1.SetTile(row, col + 1, 'S');
					counter++;
					if (counter == m_shipNum) // turns over control to player 2 after player 1 has placed all their ships
					{
						system("CLS");
						playerTurn = -1;
						counter = 0;
						display.ShowShips(m_P1);
						std::cout << "Clearing the screen in 5 seconds. Switch players now...\n";
						ClearScreen();
					}
				}
				else
				{
					PopulateBoard(m_shipNum);
				}
			}
			else if (counter == 2)
			{
				for (int i = 0; i <= counter; i++)
				{
					std::cout << "Row,Col: " << row << "," << (col+i) << std::endl;
					if (m_P1.GetTile(row, col + i) == '0')
					{
						legalPlacement = true;
					}
					else
					{
						std::cout << "\nIllegal placement of ship\n";
						legalPlacement = false;
						break;
					}
				}
				if (legalPlacement)
				{
					for(int i = 0; i <= counter; i++)
					{
						m_P1.SetTile(row, col + i, 'S');
					}
					counter++;
					if (counter == m_shipNum)
					{
						system("CLS");
						playerTurn = -1;
						counter = 0;
						display.ShowShips(m_P1);
						std::cout << "Clearing the screen in 5 seconds. Switch players now...\n";
						ClearScreen();
					}
				}
				else
				{
					PopulateBoard(m_shipNum);
				}
			}
			else if (counter == 3)
			{
				for (int i = 0; i <= counter; i++)
				{
					if (m_P1.GetTile(row, col + i) == '0')
					{
						legalPlacement = true;
					}
                    else
                    {
						std::cout << "\nIllegal placement of ship\n";
						legalPlacement = false;
                        break;
                    }
				}
				if (legalPlacement)
                {
					for(int i = 0; i <= counter; i++)
					{
						m_P1.SetTile(row,col+i, 'S');
					}
					counter++;
					if (counter == m_shipNum)
					{
						system("CLS");
						playerTurn = -1;
						counter = 0;
						display.ShowShips(m_P1);
						std::cout << "Clearing the screen in 5 seconds. Switch players now...\n";
						ClearScreen();
					}
				}
				else
				{
					PopulateBoard(m_shipNum);
				}
			}
			else if (counter == 4)
			{
				for (int i = 0; i <= counter; i++)
                {
					if (m_P1.GetTile(row, col + i) == '0')
					{
						legalPlacement = true;
					}
                    else
                    {
						std::cout << "\nIllegal placement of ship\n";
						legalPlacement = false;
                        break;
                    }
                }
                if (legalPlacement)
                {
                    for(int i = 0; i <= counter; i++)
                    {
                        m_P1.SetTile(row,col+i, 'S');
                    }
                    counter++;
					if (counter == m_shipNum)
					{
						system("CLS");
						playerTurn = -1;
						counter = 0;
						display.ShowShips(m_P1);
						std::cout << "Clearing the screen in 5 seconds. Switch players now...\n";
						ClearScreen();
					}
                }
                else
                {
                    PopulateBoard(m_shipNum);
                }
			}
			else if (counter == 5)
			{
				for (int i = 0; i <= counter; i++)
                {
                    if (m_P1.GetTile(row, col + i) == '0')
                    {
                        legalPlacement = true;
                    }
                    else
                    {
						std::cout << "\nIllegal placement of ship\n";
						legalPlacement = false;
                        break;
                    }
                }
                if (legalPlacement)
                {
                    for(int i = 0; i <= counter; i++)
                    {
                        m_P1.SetTile(row,col+i, 'S');
                    }
                    counter++;
					if (counter == m_shipNum)
					{
						system("CLS");
						playerTurn = -1;
						counter = 0;
						display.ShowShips(m_P1);
						std::cout << "Clearing the screen in 5 seconds. Switch players now...\n";
						ClearScreen();
					}
                }
                else
                {
                    PopulateBoard(m_shipNum);
                }
			}
		}
		else if(rotation == 'v') // subtracts i from row for vertical placement
		{
			if (counter == 1)
			{
				for (int i = 0; i <= counter; i++)
				{
					if (m_P1.GetTile(row - i, col) == '0')
					{
						legalPlacement = true;
					}
					else
					{
						std::cout << "\nIllegal placement of ship\n";
						legalPlacement = false;
						break;
					}
				}
				if (legalPlacement)
				{
					m_P1.SetTile(row, col, 'S');
					m_P1.SetTile(row-1, col, 'S');
					counter++;
					if (counter == m_shipNum)
					{
						system("CLS");
						playerTurn = -1;
						counter = 0;
						display.ShowShips(m_P1);
						std::cout << "Clearing the screen in 5 seconds. Switch players now...\n";
						ClearScreen();
					}
				}
				else
				{
					PopulateBoard(m_shipNum);
				}
			}
			else if (counter == 2)
			{
				for (int i = 0; i <= counter; i++)
				{
					if (m_P1.GetTile(row - i, col) == '0') 
					{
						legalPlacement = true;
					}
					else
					{
						std::cout << "\nIllegal placement of ship\n";
						legalPlacement = false;
						break;
					}
				}
				if (legalPlacement)
				{
					for(int i = 0; i <= counter; i++)
					{
						m_P1.SetTile(row-i,col, 'S');
					}
					counter++;
					if (counter == m_shipNum)
					{
						system("CLS");
						playerTurn = -1;
						counter = 0;
						display.ShowShips(m_P1);
						std::cout << "Clearing the screen in 5 seconds. Switch players now...\n";
						ClearScreen();
					}
				}
				else
				{
					PopulateBoard(m_shipNum);
				}
			}
			else if (counter == 3)
			{
	        	for (int i = 0; i <= counter; i++)
                 {
                	if (m_P1.GetTile(row - i, col) == '0')
                    {
                        legalPlacement = true;
                    }
                    else
                    {
						std::cout << "\nIllegal placement of ship\n";
						legalPlacement = false;
                        break;
                	 }
                }
                if (legalPlacement)
                {
                    for(int i = 0; i <= counter; i++)
                    {
                        m_P1.SetTile(row-i,col, 'S');
                	}
					counter++;
					if (counter == m_shipNum)
					{
						system("CLS");
						playerTurn = -1;
						counter = 0;
						display.ShowShips(m_P1);
						std::cout << "Clearing the screen in 5 seconds. Switch players now...\n";
						ClearScreen();
					}
				}
				else
				{
					PopulateBoard(m_shipNum);
				}
			}
			else if (counter == 4)
			{
	        	for (int i = 0; i <= counter; i++)
                 {
                	if (m_P1.GetTile(row - i, col) == '0') 
                    {
                        legalPlacement = true;
                    }
                    else
                    {
						std::cout << "\nIllegal placement of ship\n";
						legalPlacement = false;
                        break;
                	}
                }
                if (legalPlacement)
                {
                    for(int i = 0; i <= counter; i++)
                    {
                        m_P1.SetTile(row-i,col, 'S');
                	}
					counter++;
					if (counter == m_shipNum)
					{
						system("CLS");
						playerTurn = -1;
						counter = 0;
						display.ShowShips(m_P1);
						std::cout << "Clearing the screen in 5 seconds. Switch players now...\n";
						ClearScreen();
					}
				}
				else
				{
					PopulateBoard(m_shipNum);
				}
			}
			else if (counter == 5)
			{
	        	for (int i = 0; i <= counter; i++)
                {
                	if (m_P1.GetTile(row - i, col) == '0') 
                    {
                        legalPlacement = true;
                    }
                    else
                    {
						std::cout << "\nIllegal placement of ship\n";
						legalPlacement = false;
                        break;
                	 }
                }
                if (legalPlacement)
                {
                    for(int i = 0; i <= counter; i++)
                    {
                        m_P1.SetTile(row-i,col, 'S');
                	}
					counter++;
					if (counter == m_shipNum)
					{
						system("CLS");
						playerTurn = -1;
						counter = 0;
						display.ShowShips(m_P1);
						std::cout << "Clearing the screen in 5 seconds. Switch players now...\n";
						ClearScreen();
					}
				}
				else
				{
					PopulateBoard(m_shipNum);
				}
			}
		}
	}
	// PLAYER 2 //
	else if(playerTurn == -1)
	{
		if (counter == 0) // For a ship of size 1, rotation does not matter
		{
			m_P2.SetTile(row, col, 'S');
			counter++;
			if (counter == m_shipNum)
			{
				system("CLS");
				playerTurn = 0; // sets playerTurn to 0 to transition to StartGame();
			}
		}
		if(rotation == 'h') // adds i to col for horizontal placement
		{
			if (counter == 1)
			{
				for (int i = 0; i <= counter; i++)
				{
					if (m_P2.GetTile(row, col + i) == '0') // checks all positions that the ship will occupy first before assigning ship to a coordinate
					{
						legalPlacement = true;
					}
					else
					{
						std::cout << "\nIllegal placement of ship\n";
						legalPlacement = false;
						break;
					}
				}
				if (legalPlacement)
				{
					m_P2.SetTile(row, col, 'S');
					m_P2.SetTile(row, col + 1, 'S');
					counter++;
					if (counter == m_shipNum)
					{
						system("CLS");
						playerTurn = 0;
					}
				}
				else
				{
					PopulateBoard(m_shipNum);
				}
			}
			else if (counter == 2)
			{
				for (int i = 0; i <= counter; i++)
				{
					if (m_P2.GetTile(row, col + i) == '0') 
					{
						legalPlacement = true;
					}
					else
					{
						std::cout << "\nIllegal placement of ship\n";
						legalPlacement = false;
						break;
					}
				}
				if (legalPlacement)
				{
					for(int i = 0; i <= counter; i++)
					{
						m_P2.SetTile(row,col+i, 'S');
					}
					counter++;
					if (counter == m_shipNum)
					{
						system("CLS");
						playerTurn = 0;
					}
				}
				else
				{
					PopulateBoard(m_shipNum);
				}
			}
			else if (counter == 3)
			{
				for (int i = 0; i <= counter; i++)
				{
					if (m_P2.GetTile(row, col + i) == '0')
					{
						legalPlacement = true;
					}
					else
					{
						std::cout << "\nIllegal placement of ship\n";
						legalPlacement = false;
						break;
					}
				}
				if (legalPlacement)
				{
					for (int i = 0; i <= counter; i++)
					{
						m_P2.SetTile(row, col + i, 'S');
					}
					counter++;
					if (counter == m_shipNum)
					{
						system("CLS");
						playerTurn = 0;
					}
				}
				else
				{
					PopulateBoard(m_shipNum);
				}
			}
			else if (counter == 4)
			{
				for (int i = 0; i <= counter; i++)
				{
					if (m_P2.GetTile(row, col + i) == '0')
					{
						legalPlacement = true;
					}
					else
					{
						std::cout << "\nIllegal placement of ship\n";
						legalPlacement = false;
						break;
					}
				}
				if (legalPlacement)
				{
					for (int i = 0; i <= counter; i++)
					{
						m_P2.SetTile(row, col + i, 'S');
					}
					counter++;
					if (counter == m_shipNum)
					{
						system("CLS");
						playerTurn = 0;
					}
				}
				else
				{
					PopulateBoard(m_shipNum);
				}
			}
			else if (counter == 5)
			{
				for (int i = 0; i <= counter; i++)
				{
					if (m_P2.GetTile(row, col + i) == '0')
					{
						legalPlacement = true;
					}
					else
					{
						std::cout << "\nIllegal placement of ship\n";
						legalPlacement = false;
						break;
					}
				}
				if (legalPlacement)
				{
					for (int i = 0; i <= counter; i++)
					{
						m_P2.SetTile(row, col + i, 'S');
					}
					counter++;
					if (counter == m_shipNum)
					{
						system("CLS");
						playerTurn = 0;
					}
				}
				else
				{
					PopulateBoard(m_shipNum);
				}
			}
		}
		else if(rotation == 'v') // subtracts i from row for vertical placement
		{
			if (counter == 1)
			{
				for (int i = 0; i <= counter; i++)
				{
					if (m_P2.GetTile(row - i, col) == '0') 
					{
						legalPlacement = true;
					}
					else
					{
						std::cout << "\nIllegal placement of ship\n";
						legalPlacement = false;
						break;
					}
				}
				if (legalPlacement)
				{
					m_P2.SetTile(row, col, 'S');
					m_P2.SetTile(row-1, col, 'S');
					counter++;
					if (counter == m_shipNum)
					{
						system("CLS");
						playerTurn = 0;
					}
				}
				else
				{
					PopulateBoard(m_shipNum);
				}
			}
			else if (counter == 2)
			{
				for (int i = 0; i <= counter; i++)
				{
					if (m_P2.GetTile(row - i, col) == '0')
					{
						legalPlacement = true;
					}
					else
					{
						std::cout << "\nIllegal placement of ship\n";
						legalPlacement = false;
						break;
					}
				}
				if (legalPlacement)
				{
					for (int i = 0; i <= counter; i++)
					{
						m_P2.SetTile(row - i, col, 'S');
					}
					counter++;
					if (counter == m_shipNum)
					{
						system("CLS");
						playerTurn = 0;
					}
				}
				else
				{
					PopulateBoard(m_shipNum);
				}
			}
			else if (counter == 3)
			{
	        	for (int i = 0; i <= counter; i++)
                {
                	if (m_P2.GetTile(row - i, col) == '0') 
                    {
                        legalPlacement = true;
                    }
                    else
                    {
						std::cout << "\nIllegal placement of ship\n";
						legalPlacement = false;
                        break;
                	 }
                }
                if (legalPlacement)
                {
                    for(int i = 0; i <= counter; i++)
                    {
                        m_P2.SetTile(row-i,col, 'S');
                	}
					counter++;
					if (counter == m_shipNum)
					{
						system("CLS");
						playerTurn = 0;
					}
				}
				else
				{
					PopulateBoard(m_shipNum);
				}
			}
			else if (counter == 4)
			{
	        	for (int i = 0; i <= counter; i++)
                {
                	if (m_P2.GetTile(row - i, col) == '0') 
                    {
                        legalPlacement = true;
                    }
                    else
                    {
						std::cout << "\nIllegal placement of ship\n";
						legalPlacement = false;
                        break;
                	}
                }
                if (legalPlacement)
                {
                    for(int i = 0; i <= counter; i++)
                    {
                        m_P2.SetTile(row-i,col, 'S');
                	}
					counter++;
					if (counter == m_shipNum)
					{
						system("CLS");
						playerTurn = 0;
					}
				}
				else
				{
					PopulateBoard(m_shipNum);
				}
			}
			else if (counter == 5)
			{
	        	for (int i = 0; i <= counter; i++)
                {
                	if (m_P2.GetTile(row - i, col) == '0') 
                    {
                        legalPlacement = true;
                    }
                    else
                    {
						std::cout << "\nIllegal placement of ship\n";
						legalPlacement = false;
                        break;
                	 }
                }
                if (legalPlacement)
                {
                    for(int i = 0; i <= counter; i++)
                    {
                        m_P2.SetTile(row-i,col, 'S');
                	}
					counter++;
					if (counter == m_shipNum)
					{
						system("CLS");
						playerTurn = 0;
					}
				}
				else
				{
					PopulateBoard(m_shipNum);
				}
			}
		}
	}
}
*/

char ShipDriver::PlaceHitOrMiss(ShipBoard& board, int row, int col)
{
	if (board.GetTile(row, col) == 'S') // If tile is unhit ship
	{
		board.SetTile(row, col, 'H'); // Set tile to hit
		return('H');
	}
	else
	{
		board.SetTile(row, col, 'M'); // Set tile to miss
		return('M');
	}
}

void ShipDriver::StartGame()
{
	string coordinate;
	int adjRow = 0;
	int adjCol = 0;
	char result;
	bool win = false;

	do
	{
		if (playerTurn == 1) // Show boards
		{
			cout << "Your board\n";
			display.ShowShips(m_P1);
			cout << "\nPlayer 2's board\n";
			display.ShowHitsMisses(m_P2);
		}
		else
		{
			cout << "Your board\n";
			display.ShowShips(m_P2);
			cout << "\nPlayer 1's board\n";
			display.ShowHitsMisses(m_P1);
		}

		cout << "Make a guess: ";
		cin >> coordinate; // Player enters coordinate

		while (get<0>(ConvertCoordinate(coordinate)) == -1) // user input a bad coordinate. Gets first value of tuple. 
		{
			std::cout << "Make a guess: ";
			std::cin >> coordinate;
		}

		adjRow = get<0>(ConvertCoordinate(coordinate)); // Convert coordinate
		adjCol = get<1>(ConvertCoordinate(coordinate));

		if (playerTurn == 1) // Place hit/miss marker on other player's board and get result
		{
			result = PlaceHitOrMiss(m_P2, adjRow, adjCol);
		}
		else
		{
			result = PlaceHitOrMiss(m_P1, adjRow, adjCol);
		}

		system("CLS"); // Clear Screen

		if (playerTurn == 1) // Show boards
		{
			cout << "Your board\n";
			display.ShowShips(m_P1);
			cout << "\nPlayer 2's board\n";
			display.ShowHitsMisses(m_P2);
		}
		else
		{
			cout << "Your board\n";
			display.ShowShips(m_P2);
			cout << "\nPlayer 1's board\n";
			display.ShowHitsMisses(m_P1);
		}

		if (result == 'H') // Tell player whether they got a hit or miss
		{
			cout << "Hit! \n";
			//PlaySound("hit-explosion.wav", NULL, SND_FILENAME | SND_ASYNC);
		}
		else if (result == 'M')
		{
			cout << "Miss! \n";
			//PlaySound("miss-splash.wav", NULL, SND_FILENAME | SND_ASYNC);
		}

		system("pause"); // Pause screen
		system("CLS"); // Clear Screen

		if (playerTurn == 1) // Check if the current player has won
		{
			win = m_P2.CheckWin(); // Check if P2's board has any S's left
		}
		else
		{
			win = m_P1.CheckWin(); // Check if P1's board has any S's left
		}

		if (win == false) // Switch players if no one has won
		{
			playerTurn = playerTurn * -1;
		}
	} while (win == false);
	
	if (playerTurn == 1) // Display win message
	{
		cout << "Player 1 wins! \n";
	}
	else
	{
		cout << "Player 2 wins! \n";
	}

	system("pause");
	system("cls");
}

void ShipDriver::ClearScreen()
{
	std::this_thread::sleep_for(std::chrono::milliseconds(5000));
	system("CLS");
}
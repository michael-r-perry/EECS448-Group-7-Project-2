#include "ShipDriver.h"
#include "DisplayBoard.h"
#include "ShipBoard.h"
#include <iostream>
#include <tuple>
using namespace std;

ShipDriver::ShipDriver()
{
	m_shipNum = 0;
	playerTurn = 1;
	counter = 0;
	SetUpBoard();
}

void ShipDriver::SetUpBoard()
{
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
	std::cout << endl;
	char input;
	string coordinate;
	int adjRow; // the adjusted row value after converting the user's coordinate
	int adjCol; // the adjusted column value after converting the user's coordinate

	// Player 1:
	do
	{
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

			/* CODE TO IMPLEMENT HERE: 
			* MARK THE LOCATION ON THE BOARD. DISPLAY UPDATED BOARD TO PLAYER.
			* NEED SOME WAY OF PLACING THE PIECES VERTICAL/HORIZONTAL FOR ANY SHIP > 1X1.
			* ALSO NEED TO CHECK THAT PLACING THE PIECE HORIZONTAL/VERTICAL WON'T GO OFF THE BOARD
			* AND/OR OVERLAP WITH ANOTHER SHIP. 
			*/
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
	} while (counter < m_shipNum);
 
	counter = 0; // initializes counter back to zero for Player 2
	display.ShowShips(m_P1);

	/*
	* Create a method in DisplayBoard that will notify the user that the screens are about to swtich to the other player.
	* The function will then clear the terminal before proceeding to Player 2's ship placement.
	*/

	// Player 2
	do
	{
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
	} while (counter < m_shipNum);

	// Start the game
	StartGame();
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
	int col = tolower(coordinate.at(0)) - 'a';
	int row = coordinate.at(1) - '0' - 1; // only grabs the second index position of the string. Eliminates possibility of player typing "A1234"

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
	bool legalPlacement;
	if(playerTurn == 1)
	{

		//For a  ship of size 1 rotation does not matter
		if (counter == 0)
		{
			m_P1.SetTile(row, col, 'S');
			counter++;
		}

		if(rotation == 'h')
		{
			if (counter == 1)
			{
				for (int i = 0; i <= counter; i++)
				{
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
					for(int i = 0; i <= counter; i++)
					{
						m_P1.SetTile(row,col+i, 'S');
					}
				/*
					m_P1.SetTile(row, col, 'S');
					m_P1.SetTile(row, col + 1, 'S');
					m_P1.SetTile(row, col + 2, 'S');
				*/	
					counter++;
				}
				else
				{
					PopulateBoard(m_shipNum);
				}
			}
			else if (counter == 3)
			{
				// copy paste code from previous else if here. Make sure to include an extra SetTile for each increasing value of counter :
	                        for (int i = 0; i <= counter; i++)
                                {
                                        if (m_P1.GetTile(row, col + i) == '0') // checks all positi$
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
                                        if (m_P1.GetTile(row, col + i) == '0') // checks all positi$
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
                                        if (m_P1.GetTile(row, col + i) == '0') // checks all positi$
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
                                }
                                else
                                {
                                        PopulateBoard(m_shipNum);
                                }
			}
		}
		else if(rotation == 'v')
		{
			if (counter == 1)
			{
				for (int i = 0; i <= counter; i++)
				{
					if (m_P1.GetTile(row - i, col) == '0') // checks all positions that the ship will occupy first before assigning ship to a coordinate
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
					if (m_P1.GetTile(row - i, col) == '0') // checks all positions that the ship will occupy first before assigning ship to a coordinate
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
				/*
					m_P1.SetTile(row, col, 'S');
					m_P1.SetTile(row - 1, col, 'S');
					m_P1.SetTile(row - 2, col, 'S');
				*/	
					counter++;
				}
				else
				{
					PopulateBoard(m_shipNum);
				}
			}
			else if (counter == 3)
			{
				// copy paste code from previous else if here. Make sure to include an extra SetTile for each increasing value of counter :
	        	for (int i = 0; i <= counter; i++)
                 {
                	if (m_P1.GetTile(row - i, col) == '0') // checks all positi$
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
				}
				else
				{
					PopulateBoard(m_shipNum);
				}

			}
			else if (counter == 4)
						{
				// copy paste code from previous else if here. Make sure to include an extra SetTile for each increasing value of counter :
	        	for (int i = 0; i <= counter; i++)
                 {
                	if (m_P1.GetTile(row - i, col) == '0') // checks all positi$
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
				}
				else
				{
					PopulateBoard(m_shipNum);
				}

			}
			else if (counter == 5)
			{
				// copy paste code from previous else if here. Make sure to include an extra SetTile for each increasing value of counter :
	        	for (int i = 0; i <= counter; i++)
                 {
                	if (m_P1.GetTile(row - i, col) == '0') // checks all positi$
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
				}
				else
				{
					PopulateBoard(m_shipNum);
				}

			}
		}
		
	}
	else if(playerTurn == -1)
	{
		//For a  ship of size 1 rotation does not matter
		if (counter == 0)
		{
			m_P1.SetTile(row, col, 'S');
			counter++;
		}

		if(rotation == 'h')
		{
			if (counter == 1)
			{
				for (int i = 0; i <= counter; i++)
				{
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
					for(int i = 0; i <= counter; i++)
					{
						m_P2.SetTile(row,col+i, 'S');
					}
					counter++;
				}
				else
				{
					PopulateBoard(m_shipNum);
				}
			}
			else if (counter == 3)
			{
				// copy paste code from previous else if here. Make sure to include an extra SetTile for each increasing value of counter :
	                        for (int i = 0; i <= counter; i++)
                                {
                                        if (m_P2.GetTile(row, col + i) == '0') // checks all positi$
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
                                        if (m_P2.GetTile(row, col + i) == '0') // checks all positi$
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
                                        if (m_P2.GetTile(row, col + i) == '0') // checks all positi$
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
                                }
                                else
                                {
                                        PopulateBoard(m_shipNum);
                                }
			}
		}
		else if(rotation == 'v')
		{
			if (counter == 1)
			{
				for (int i = 0; i <= counter; i++)
				{
					if (m_P1.GetTile(row - i, col) == '0') // checks all positions that the ship will occupy first before assigning ship to a coordinate
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
					if (m_P1.GetTile(row - i, col) == '0') // checks all positions that the ship will occupy first before assigning ship to a coordinate
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
				/*
					m_P1.SetTile(row, col, 'S');
					m_P1.SetTile(row - 1, col, 'S');
					m_P1.SetTile(row - 2, col, 'S');
				*/	
					counter++;
				}
				else
				{
					PopulateBoard(m_shipNum);
				}
			}
			else if (counter == 3)
			{
				// copy paste code from previous else if here. Make sure to include an extra SetTile for each increasing value of counter :
	        	for (int i = 0; i <= counter; i++)
                 {
                	if (m_P1.GetTile(row - i, col) == '0') // checks all positi$
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
				}
				else
				{
					PopulateBoard(m_shipNum);
				}

			}
			else if (counter == 4)
						{
				// copy paste code from previous else if here. Make sure to include an extra SetTile for each increasing value of counter :
	        	for (int i = 0; i <= counter; i++)
                 {
                	if (m_P1.GetTile(row - i, col) == '0') // checks all positi$
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
				}
				else
				{
					PopulateBoard(m_shipNum);
				}

			}
			else if (counter == 5)
			{
				// copy paste code from previous else if here. Make sure to include an extra SetTile for each increasing value of counter :
	        	for (int i = 0; i <= counter; i++)
                 {
                	if (m_P1.GetTile(row - i, col) == '0') // checks all positi$
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
				}
				else
				{
					PopulateBoard(m_shipNum);
				}

			}
		}
	}
}

void ShipDriver::StartGame()
{
	while(!CheckWin())
	{
		
	}
}

bool ShipDriver::CheckWin()
{
	return(false);
}

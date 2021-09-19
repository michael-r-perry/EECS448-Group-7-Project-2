#include <iostream>
#include "DisplayBoard.h"
#include "ShipBoard.h"
<<<<<<< HEAD
=======

>>>>>>> 59916217c2b7a5d963c38504b7efd299ff559e91
using namespace std;

void DisplayBoard::ShowShips(ShipBoard& ship)
{
	std::cout << "  A B C D E F G H I J\n";
	int rowCounter = 1;
	char tile;

	for (int i = 0; i < rows; i++)
	{
		cout << rowCounter << " ";
		for (int j = 0; j < columns; j++)
		{
			tile = ship.GetTile(i, j);

			if ((tile == 'S') || (tile == 'H'))
			{
				cout << tile << " ";
			}
			else
			{
				cout << '0' << " ";
			}
		}

	std::cout << "\n";
	rowCounter += 1;
	}
}

void DisplayBoard::ShowHitsMisses(ShipBoard& ship)
{
	std::cout << "  A B C D E F G H I J\n";
	int rowCounter = 1;
	char tile;

	for (int i = 0; i < rows; i++)
	{
		cout << rowCounter << " ";
		for (int j = 0; j < columns; j++)
		{
			tile = ship.GetTile(i, j);

			if ((tile == 'H') || (tile == 'M'))
			{
				cout << tile << " ";
			}
			else
			{
				cout << '0' << " ";
			}
		}

	std::cout << "\n";
	rowCounter += 1;
	}
}
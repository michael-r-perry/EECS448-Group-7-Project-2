#include <iostream>
#include "DisplayBoard.h"
#include "ShipBoard.h"
#include "ShipBoard.cpp"
using namespace std;

void DisplayBoard::ShowBoard(ShipBoard& Ship)
{
	std::cout << "  A B C D E F G H I J\n";
	int rowCounter = 1;
		for (int i = 0; i < rows; i++)
		{
			cout << rowCounter << " ";
			for (int j = 0; j < columns; j++)
			{
				std::cout << Ship.GetTile(i,j) << " ";
			}
		std::cout << "\n";
		rowCounter += 1;
		}
}
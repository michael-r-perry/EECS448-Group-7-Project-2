#include <iostream>
#include "ShipBoard.h"
using namespace std;

bool ShipBoard::CheckWin()
{
	// Loop through board, return false if an unhit ship tile is found
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			if (board[i][j] == 'O')
			{
				return(false);
			}
		}
	}

	// If no unhit ship tiles are found, return true
	return(true);
}

void ShipBoard::SetTile(int row, int column, char marker)
{
	board[row][column] = marker;
}

char ShipBoard::GetTile(int row, int column)
{
	return(board[row][column]);
}
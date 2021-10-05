#include <iostream>
#include "ShipBoard.h"
using namespace std;

ShipBoard::ShipBoard()
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			board[i][j] = '0';
		}
	}
}

bool ShipBoard::CheckWin()
{
	// Loop through board, return false if an unhit ship tile is found
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			if (board[i][j] == 'S')
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
	try
	{
		if ((row < rows) and (column < columns)) // Check if row and column is in bound
		{
			board[row][column] = marker;
		}
		else
		{
			throw runtime_error("Can't set tile outside range!");
		}
	}
	catch (exception e)
	{
		cout << "Runtime Error: " << e.what();
	}
}

char ShipBoard::GetTile(int row, int column)
{
	try
	{
		if ((row < rows) and (column < columns)) // Check if row and column is in bound
		{
			return(board[row][column]);
		}
		else
		{
			throw runtime_error("Can't get tile outside range!");
		}
	}
	catch(exception e)
	{
		cout << "Runtime Error: " << e.what();
	}
}
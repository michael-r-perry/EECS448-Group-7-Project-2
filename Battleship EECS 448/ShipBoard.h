/*
	This class stores a board containing ship locations as well as where ships have been hit. 
	E = empty space
	O = ship
	X = hit
*/

#pragma once
#ifndef SHIPBOARD_H
#define SHIPBOARD_H

class ShipBoard
{
	private:
		int rows = 9; // number of rows of board
		int columns = 10; // number of columns of board
		char board[rows][columns]; // Board containing ship locations
	public:
		/*
		@pre: Board is valid
		@post: None
		@param: None
		@return: True if board satisfies win condition, false if not
		*/
		bool CheckWin();

		/*
		@pre: Row and column are in range, marker is valid
		@post: Specified marker is placed at specified location on board
		@param: None
		@return: None
		*/
		void SetTile(int row, int column, char marker);

		/*
		@pre: Row and column are in range
		@post: None
		@param: None
		@return: marker at specified tile
		*/
		char GetTile(int row, int column);
};

#endif
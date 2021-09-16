#ifndef SHIPDRIVER_H
#define SHIPDRIVER_H

#include <iostream>
#include <stdexcept>
#include <tuple>
#include "ShipBoard.h"
#include "DisplayBoard.h"

class ShipDriver
{
	private:
		ShipBoard m_P1;
		ShipBoard m_P2;
		int m_shipNum; // Number of ships chosen
		int playerTurn; // Stores the current turn. Value initialized to 1 for Player One, -1 for Player Two. Multiply by -1 to change turns. 
		int counter = 0; // Counter used to ensure all ships have been placed
	

	public:

		ShipDriver();
	
		/*
		@pre: None
		@post: Gets the desired number of ships from the player
		@param: None
		@return: None
		*/
	
		void SetUpBoard();

		/*
		@pre: None
		@post: Initializes the start of the game
		@param: None
		@return: None
		*/
		//void StartGame();

		/*
		@pre: None
		@post: None
		@param: None
		@return: True if board satisfies win condition, false if not
		*/
		bool CheckWin();

		/*
		@pre: Get the number of ships from SetUpBoard() method
		@post: Get's position for each ship and populates the board
		@param: Number of ships that will be in play, an integer
		@return: None
		*/
		void PopulateBoard(int m_shipNum);

		/*
		@pre: Get coordinate from player. For example, "A1"
		@post: Converts the alphanumeric coordinate to a row and column on the board. 
		@param: The coordinate string
		@return: The row and column of the ship's placement as tuple. Returns -1 on bad input in first index location of tuple. 
		*/
		std::tuple<int, int> ConvertCoordinate(std::string coordinate);
};
#endif

#ifndef SHIPDRIVER_H
#define SHIPDRIVER_H

#include <iostream>
#include <stdexcept>
#include "ShipBoard.h"
#include "DisplayBoard.h"

class ShipDriver
{
	private:
		ShipBoard m_P1;
		ShipBoard m_P2;
		int m_P1ShipNum; // Number of ships chosen by Player 1
		int m_P2ShipNum; // Number of ships chosen by Player 2
		int playerTurn; // Stores the current turn. Value initialized to 1 for Player One, -1 for Player Two. Multiply by -1 to change turns. 
	

	public:

		ShipDriver();
	
		/*
		@pre: None
		@post: Sets up ship locations and marks them on the respective player's shipBoard
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
		@pre: Get both user's desired number of ships
		@post: Get's position for each ship and populate's board
		@param: Number of ships for both players, integer. 
		@return: None
		*/
		void PopulateBoard(int m_P1ShipNum, int m_P2ShipNum);
};
#endif

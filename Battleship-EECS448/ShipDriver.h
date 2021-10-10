#ifndef SHIPDRIVER_H
#define SHIPDRIVER_H

#include <iostream>
#include <stdexcept>
#include <tuple>
#include "ShipBoard.h"
#include "DisplayBoard.h"
#include "AI.h"

class ShipDriver
{
	private:
		ShipBoard m_P1; // player 1's board
		ShipBoard m_P2; // player 2's board
		DisplayBoard display;
		AI m_AI;
		bool m_ifAI;
		int m_shipNum; // Number of ships chosen
		int playerTurn; // Stores the current turn. Value initialized to 1 for Player One, -1 for Player Two. Multiply by -1 to change turns. 
		int counter; // Counter used to ensure all ships have been placed

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
		@post: Runs the main loop of the game, also checking for super shot input
		@param: None
		@return: None
		*/
		void StartGame();

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

		/*
		@pre: Get row and column of ship along with its orientation
		@post: Mark Ship Loction at Row/Col
		@param: Coordinates (row, col), and the orientation for the ship
		@return: None
		*/
		void PlaceShip(int row, int col, char rotation); //We can change this to a tuple I just don't know how to use them ATM

		/*
		@pre: row and col must be valid
		@post: tile is marked as a hit or miss on the specified board
		@param: Coordinates (row, col), and the orientation for the ship
		@return: H if hit, M if miss
		*/
		char PlaceHitOrMiss(ShipBoard& board, int row, int col);

		/*
		@pre: None
		@post: Clear's the terminal screen after a 5 second delay
		@param: None
		@return: None
		*/
		void ClearScreen();

        /*
        @pre: None
        @post: Finds correct OS and clears screen based off OS
        @param: None
        @return: None
        */
       void Clear();
};
#endif

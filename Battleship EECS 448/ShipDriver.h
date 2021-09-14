#ifndef SHIPDRIVER_H
#define SHIPDRIVER_H

#include <iostream>
#include <stdexcept>
#include "ShipBoard.h";
#include "DisplayBoard.h";

class ShipDriver
{
	private:
	ShipBoard m_P1;
	ShipBoard m_P2;
	
	

	public:
	ShipDriver();
	
	/*
	@pre: None
	@post: Sets up ship locations and marks them on the respective player's shipBoard
	@return: None
	/*
	void setUpBoard();

	/*
	@pre: None
	@post: Initializes the start of the game
	@return: None
	*/
	void startGame();

	/*
	@pre: None
	@post: None
	@return: True if board satisfies win condition, false if not
	*/
	bool checkWin();
};
#endif

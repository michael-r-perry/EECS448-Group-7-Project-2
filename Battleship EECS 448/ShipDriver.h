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
	int m_P1ShipNum;
	int m_P2ShipNum;
	

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
};
#endif

#pragma once
#ifndef DISPLAYBOARD_H
#define DISPLAYBOARD_H
#include "ShipBoard.h"

class DisplayBoard {
public:
	/*
	@pre: None
	@post: Displays the game board to user
	@param: A ShipBoard class object
	@return: None
	*/
	void ShowBoard(ShipBoard& Ship);

private:
	int rows = 9; /**<The number of rows.>*/
	int columns = 10; /**<The number of columns.>*/
};

#endif

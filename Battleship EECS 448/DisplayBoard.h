#pragma once
#ifndef DISPLAYBOARD_H
#define DISPLAYBOARD_H
#include "ShipBoard.h"

class DisplayBoard {
public:
	/*
	@pre: None
	@post: Displays the specified board with only ship locations to user
	@param: A ShipBoard class object
	@return: None
	*/
	void ShowShips(ShipBoard& ship);

	/*
	@pre: None
	@post: Displays the specified board with only hits/misses to user
	@param: A ShipBoard class object
	@return: None
	*/
	void ShowHitsMisses(ShipBoard& ship);

private:
	int rows = 9; /**<The number of rows.>*/
	int columns = 10; /**<The number of columns.>*/
};

#endif

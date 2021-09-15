#pragma once
#ifndef DISPLAYBOARD_H
#define DISPLAYBOARD_H

class DisplayBoard {
public:
	/*
	@pre: None
	@post: Displays the game board to user
	@param: None
	@return: None
	*/
	void ShowBoard();

private:
	int shipNum; /**<The number of ships selected by the player.>*/
	int rows = 9; /**<The number of rows.>*/
	int columns = 10; /**<The number of columns.>*/
};

#endif

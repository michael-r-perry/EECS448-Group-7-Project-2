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

	/*
	@pre: None
	@post: Initializes all values of the game board to "0"
	@param: None
	@return: None
	*/
	void Init();

	/*
	@pre: NumOfShipsPrompt must successfully aquire the number of ships from the player
	@post: Stores the number of ships chosen for easy access
	@param: None
	@return: Integer number of ships
	*/
	int NumOfShips();

	/*
	@pre: None
	@post: Gets the number of ships and passes that info to NumOfShips.
	@param: None
	@return: None
	*/
	void NumOfShipsPrompt();

private:
	int shipNum; /**<The number of ships selected by the player.>*/
	int rows = 9; /**<The number of rows.>*/
	int columns = 10; /**<The number of columns.>*/
};

#endif

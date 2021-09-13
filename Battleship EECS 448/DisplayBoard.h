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
	@pre: None
	@post: Acquires the desired number of ships from the player
	@param: None
	@return: Integer number of ships
*/
	int NumOfShips();

private:
	int rows = 9; /**<Number of rows for the game board>*/
	int cols = 10; /**<Number of columns for the game board>*/
	int board[9][10]; /**<The game board itself>*/
	int shipNum; /**<The number of ships selected by the player.>*/
};

#endif

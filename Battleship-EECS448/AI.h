#ifndef AI_H
#define AI_H

#include <tuple>
#include "ShipBoard.h"

class AI
{
    public:
        AI();

        /*
	    @pre: There exists a board for player 1
	    @post: Sets the difficulty of the game and stores P1's board in map member variable
	    @param: A character for selected difficulty and a ShipBoard class object
	    @return: None
	    */
        void setDifficulty(char difficulty, ShipBoard& board);

        /*
	    @pre: None
	    @post: Randomly selects orientation for an AI ship placement between vertical and horizontal
	    @param: None
	    @return: A char for the selected orientation
	    */
        char selectOrientation();

        /*
	    @pre: None
	    @post: A ship is placed at a randomly selected coordinate
	    @param: A char for the orientation and a counter to show what ship is being placed
	    @return: A tuple containing the coordinates to place a ship at
	    */
        std::tuple<int, int> placeShip(char orientation, int counter);

        /*
	    @pre: None
	    @post: updates the map ShipBoard object and chooses which difficulty of AI will shoot
	    @param: A ShipBoard object for player 1
	    @return: A tuple containing the coordinates to shoot at, based on the difficulty
	    */
        std::tuple<int, int> Shoot(ShipBoard& board);

        /*
	    @pre: A shot has been fired by shootMedium
	    @post: Checks to see if the medium AI just hit a ship and needs to change behavior
	    @param: A char corresponding to the result of a shot
	    @return: None
	    */
        void HandleResult(char result);

    private:
        /*
	    @pre: None
	    @post: Randomly generates coordinates for a shot and returns the values
	    @param: None
	    @return: A tuple containing coordinates
	    */
        std::tuple<int, int> easyShoot();

        /*
	    @pre: None
	    @post: Returns random coordinates until a ship is hit, then cycles through adjacent options
	    @param: None
	    @return: A tuple containing coordinates
	    */
        std::tuple<int, int> mediumShoot();

        /*
	    @pre: None
	    @post: Returns the results for hardShootHelper
	    @param: None
	    @return: A tuple containing coordinates
	    */
        std::tuple<int, int> hardShoot();

        /*
	    @pre: None
	    @post: Searches for the location of a ship, working left-to-right, top-to-bottom and returns the coordinates
	    @param: None
	    @return: A tuple containing coordinates
	    */
        std::tuple<int, int> hardShootHelper();

        /*
	    @pre: None
	    @post: flips the direction of the next coordinate to search in mediumShoot
	    @param: None
	    @return: None
	    */
        void flipDirection();

        /*
	    @pre: None
	    @post: Checks to see if the given values are in the coordinates
	    @param: Two ints, one for the row and another for the column
	    @return: A char that tells if the coordinates are valid
	    */
        bool isValidCoords(int row, int col);

        ShipBoard map;
        char m_difficulty;
        bool m_randomShoot;
        bool m_searching;
        bool m_firstDirection;
        int m_direction;
        std::tuple<int, int> m_directions[4];
        int rowOrig;
        int colOrig;
        int rowMark;
        int colMark;
};
#endif

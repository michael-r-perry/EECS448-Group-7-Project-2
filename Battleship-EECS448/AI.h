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
	    @post: Displays the specified board with only hits/misses to user
	    @param: None
	    @return: A tuple containing the coordinates to shoot at, based on the difficulty
	    */
        std::tuple<int, int> Shoot();

        /*
	    @pre: None
	    @post: Displays the specified board with only hits/misses to user
	    @param: A ShipBoard class object
	    @return: None
	    */
        void HandleResult(char result);

    private:
        /*
	    @pre: None
	    @post: Displays the specified board with only hits/misses to user
	    @param: A ShipBoard class object
	    @return: None
	    */
        std::tuple<int, int> easyShoot();

        /*
	    @pre: None
	    @post: Displays the specified board with only hits/misses to user
	    @param: A ShipBoard class object
	    @return: None
	    */
        std::tuple<int, int> mediumShoot();

        /*
	    @pre: None
	    @post: Displays the specified board with only hits/misses to user
	    @param: A ShipBoard class object
	    @return: None
	    */
        std::tuple<int, int> hardShoot();

        /*
	    @pre: None
	    @post: Displays the specified board with only hits/misses to user
	    @param: A ShipBoard class object
	    @return: None
	    */
        std::tuple<int, int> hardShootHelper();

        /*
	    @pre: None
	    @post: Displays the specified board with only hits/misses to user
	    @param: A ShipBoard class object
	    @return: None
	    */
        void flipDirection();

        /*
	    @pre: None
	    @post: Displays the specified board with only hits/misses to user
	    @param: A ShipBoard class object
	    @return: None
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

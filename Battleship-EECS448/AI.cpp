#include "AI.h"
#include <iostream>
#include <stdlib.h>
#include <tuple>
using namespace std;

AI::AI()
{
    m_difficulty = 'E'; // Default value
    m_randomShoot = true;
    m_searching = false;
    m_firstDirection = false;
    m_direction = 0;
    m_directions[0] = make_tuple(-1,0); // Up
    m_directions[1] = make_tuple(0,1);  // Right
    m_directions[2] = make_tuple(1,0);  // Down
    m_directions[3] = make_tuple(0,-1); // Left
    cout << "Direction 0: " << get<0>(m_directions[m_direction]) << ", " << get<1>(m_directions[m_direction]) << endl;
    cout << "Direction 1: " << get<0>(m_directions[1]) << ", " << get<1>(m_directions[1]) << endl;
    cout << "Direction 2: " << get<0>(m_directions[2]) << ", " << get<1>(m_directions[2]) << endl;
    cout << "Direction 3: " << get<0>(m_directions[3]) << ", " << get<1>(m_directions[3]) << endl;
}

void AI::setDifficulty(char difficulty)
{
    if ((difficulty == 'E' || difficulty == 'M') || difficulty == 'H')
    {
        m_difficulty = difficulty;
    }
    else
    {
        throw("Invalid difficulty type ('E', 'M', 'H' are valid).");
    }
}

char AI::selectOrientation()
{
    int num = rand() % 2;
    if (num == 0) 
    {
        return 'h';
    }
    else // num == 1
    {
        return 'v';
    }
}

std::tuple<int, int> AI::placeShip(char orientation, int counter)
{
    int row;
    int col;
    // extra logic to catch out-of-bounds placement
    if (orientation == 'h')
    {
        row = rand() % 9;
        col = rand() % (10 - counter);
    }
    else // orientation == 'v'
    {
        row = rand() % (9 - counter) + counter;
        col = rand() % 10;
    }
    return make_tuple(row, col);
}

std::tuple<int, int> AI::Shoot()
{
    if (m_difficulty == 'E')
    {
        return easyShoot();
    }
    else if (m_difficulty == 'M')
    {
        return mediumShoot();
    }
    else if (m_difficulty == 'H')
    {
        return hardShoot();
    }
    else 
    {
        throw("m_difficulty not valid for Shoot().");
    }
}

std::tuple<int, int> AI::easyShoot()
{
    return make_tuple(rand() % 9, rand() % 10); // Placeholder
}

/*
bool m_randomShoot
bool m_searching

if m_randomShoot
    random shoot
else
    if m_searching
        find direction of ship
    else
        shoot in line
*/
std::tuple<int, int> AI::mediumShoot()
{
    std::tuple<int, int> coords = make_tuple(0,0);

    if (m_randomShoot) // Randomly Shooting Phase
    {
        rowMark = rand() % 9;
        colMark = rand() % 10;
        cout << "RANDOM SHOT (row,col): " << rowMark << "," << colMark << endl;
        coords = make_tuple(rowMark, colMark);
    }
    else if (m_searching) // Searching for Ship Direction Phase
    {
        cout << "PRE SEARCHING SHOT (row,col,dir): " << rowMark << "," << colMark << "," << m_direction << endl;
        cout << "PRE SEARCHING SHOT (rowOrig,colOrig): " << rowOrig << "," << colOrig << endl;
        cout << "Direction (get0,get1): " << get<0>(m_directions[m_direction]) << "," << get<1>(m_directions[m_direction]) << endl;
        rowMark = rowOrig + get<0>(m_directions[m_direction]);
        colMark = colOrig + get<1>(m_directions[m_direction]);
        cout << "POST SEARCHING SHOT (row,col,dir): " << rowMark << "," << colMark << "," << m_direction << endl;
        if (isValidCoords(rowMark, colMark))
        {
            cout << "SEARCHING SHOT (row,col,dir): " << rowMark << "," << colMark << "," << m_direction << endl;
            coords = make_tuple(rowMark, colMark);
        }
        else
        {
            m_direction++; // On edge, try next direction
            if (m_direction >= 4) // if through all directions return to random shooting
            {
                m_randomShoot = true;
                m_searching = false;
                m_direction = 0;
            }
            coords = mediumShoot(); // try next direction or return to random
        }
    }
    else if (m_firstDirection) // Shooting in the First Direction Phase after hit in Searching Phase
    {
        int row = rowMark + get<0>(m_directions[m_direction]);
        int col = colMark + get<1>(m_directions[m_direction]);
        if (isValidCoords(row, col))
        {
            rowMark = row;
            colMark = col;
            cout << "FIRST DIRECTION SHOT (row,col,dir): " << rowMark << "," << colMark << "," << m_direction << endl;
            coords = make_tuple(rowMark, colMark);
        }
        else
        {
            m_firstDirection = false; // end of board in this direction
            if (m_direction >= 2) // if down or left, up or right was already checked in search phase
            {                     // Ship complete, return to random shooting
                m_randomShoot = true;
                m_direction = 0;
            }
            else // Start shooting in opposite direction
            {
                flipDirection();
                rowMark = rowOrig;
                colMark = colOrig;
            }
            coords = mediumShoot(); // try Second Direction or return to Random
        }
    }
    else // Shooting in the Second Direction Phase after miss in First Direction Phase
    {
        int row = rowMark + get<0>(m_directions[m_direction]);
        int col = colMark + get<1>(m_directions[m_direction]);
        if (isValidCoords(row, col))
        {
            rowMark = row;
            colMark = col;
            cout << "SECOND DIRECTION SHOT (row,col,dir): " << rowMark << "," << colMark << "," << m_direction << endl;
            coords = make_tuple(rowMark, colMark);
        }
        else
        {
            m_randomShoot = true;
            m_direction = 0;
            coords = mediumShoot();
        }
    }
    return coords; // Placeholder
}

std::tuple<int, int> AI::hardShoot()
{
    return make_tuple(0,0); // Placeholder
    /*
    rowMark = 1;
    colMark = 1;
    coordinates = hardShootHelper();
    (value at coordinates) = 'H';
    */
}

std::tuple<int, int> AI::hardShootHelper()
{
    return make_tuple(0,0); // Placeholder
    /*
    std::tuple<int, int> coordinates; 
    
    if(value at coordinate == 'S'){

        return(coordinates<rowMark, colMark>);
    }
    else {

        if(rowMark == 9){

        colMark++;
        rowMark = 1;
        }
        else{

        rowMark++;
        }
        hardShootHelper();
    }
    //recursively work through board and return a pair for the first unhit ship found
    */
}

void AI::HandleResult(char result) 
{
    if (m_difficulty == 'M')
    {
        // See which phase of shooting the medium AI is in
        if (m_randomShoot)
        {
            cout << "RANDOM Handle (row,col): " << rowMark << "," << colMark << endl;
            if (result == 'H')
            {
                rowOrig = rowMark;
                colOrig = colMark;
                m_randomShoot = false;
                m_searching = true;
                m_direction = 0;
            }
            // if result == 'M' stay on random shooting
        }
        else if (m_searching)
        {
            cout << "SEARCHING Handle (row,col,dir): " << rowMark << "," << colMark << "," << m_direction << endl;
            if (result == 'M')
            {
                m_direction++; // Search at the next direction
                if (m_direction >= 4) // if no hits all the way around return to random
                {
                    m_randomShoot = true;
                    m_searching = false;
                    m_direction = 0;
                }
            }
            else // result == 'H'
            {
                m_searching = false;
                m_firstDirection = true;
            }
        }
        else if (m_firstDirection)
        {
            cout << "FIRST DIRECTION Handle (row,col,dir): " << rowMark << "," << colMark << "," << m_direction << endl;
            if (result == 'M')
            {
                m_firstDirection = false;
                if (m_direction >= 2) // if down or left, up or right was already checked in search phase
                {                     // Reset properties to random shooting
                    m_randomShoot = true;
                    m_direction = 0;
                }
                else // flip the direction and shoot that way
                {
                    flipDirection();
                    rowMark = rowOrig;
                    colMark = colOrig;
                }
            }
            // if result == 'H' stay on shooting first direction
        }
        else // Second Direction
        {
            cout << "SECOND DIRECTION Handle (row,col,dir): " << rowMark << "," << colMark << "," << m_direction << endl;
            if (result == 'M')
            {
                m_randomShoot = true;
                m_direction = 0;
            }
            // if result == 'H' stay on shooting second direction
        }
    }
}

void AI::flipDirection()
{
    if      (m_direction == 0) m_direction = 2;
    else if (m_direction == 1) m_direction = 3;
    else if (m_direction == 2) m_direction = 0;
    else if (m_direction == 3) m_direction = 1; 
}

bool AI::isValidCoords(int row, int col)
{
    return ((row >= 0 && row <= 8) && (col >= 0 && col <= 9));
}
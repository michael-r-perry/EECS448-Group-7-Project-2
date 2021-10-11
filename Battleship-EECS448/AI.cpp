#include "AI.h"
#include <iostream>
#include <stdlib.h>
#include <tuple>
#include "ShipBoard.h"
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
}

void AI::setDifficulty(char difficulty, ShipBoard& board)
{
    map = board;
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

std::tuple<int, int> AI::Shoot(ShipBoard& board)
{
    map = board;
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
    return make_tuple(rand() % 9, rand() % 10); // random Row(0-8) Col(0-9)
}

std::tuple<int, int> AI::mediumShoot()
{
    std::tuple<int, int> coords = make_tuple(0,0);

    if (m_randomShoot) // Randomly Shooting Phase
    {
        rowMark = rand() % 9;
        colMark = rand() % 10;
        coords = make_tuple(rowMark, colMark);
    }
    else if (m_searching) // Searching for Ship Direction Phase
    {
        rowMark = rowOrig + get<0>(m_directions[m_direction]);
        colMark = colOrig + get<1>(m_directions[m_direction]);
        if (isValidCoords(rowMark, colMark))
        {
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
    rowMark = 0;
    colMark = 0;
    std::tuple<int, int> coords;
    coords = hardShootHelper();
    return coords;
}

std::tuple<int, int> AI::hardShootHelper()
{ 
    if(map.GetTile(rowMark, colMark) == 'S'){

        std::tuple<int, int> coords = make_tuple(rowMark, colMark);
        return coords;
    }
    else {

        if(colMark == 9){

            rowMark++;
            colMark = 0;
        }
        else{

            colMark++;
        }
        hardShootHelper();
    }
    std::tuple<int, int> coords = make_tuple(rowMark, colMark);
    return coords; // Placeholder
}

void AI::HandleResult(char result) 
{
    if (m_difficulty == 'M')
    {
        // See which phase of shooting the medium AI is in
        if (m_randomShoot)
        {
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
#include "AI.h"
#include <stdlib.h>
#include <tuple>
using namespace std;

AI::AI()
{
    m_difficulty = 'E'; // Default value
    m_randomShoot = true;
    m_searching = false;
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
<<<<<<< HEAD
    return make_tuple(0, 0); // Placeholder
=======
  return make_tuple(rand() % 9, rand() % 10); // Placeholder
>>>>>>> fab9bfd9b1f2d79dd82115df9ab3389d76b1753b
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

    if (m_randomShoot)
    {
        int row = rand() % 9;
        int col = rand() % 10;
        coords = make_tuple(row, col);
    }
    else 
    {
        if (m_searching) 
        {
            
        }
        else
        {

        }
    }
    return coords // Placeholder
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
<<<<<<< HEAD
    return make_tuple(0,0); // Placeholder
    /*
    std::tuple<int, int> coordinates; 
    
    if(value at coordinate == 'S'){
=======
  return make_tuple(0,0); // Placeholder
  /*
  std::tuple<int, int> coordinates;

  if(value at coordinate == 'S'){
>>>>>>> fab9bfd9b1f2d79dd82115df9ab3389d76b1753b

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
        if (result == 'H')
        {
            m_randomShoot = false;
            m_searching = true;
        }
        else // result == 'M'
        {
            m_randomShoot = true;
            m_searching = false;
        }
    }
<<<<<<< HEAD
}
=======
    hardShootHelper();
  }
  //recursively work through board and return a pair for the first unhit ship found
  */
}
>>>>>>> fab9bfd9b1f2d79dd82115df9ab3389d76b1753b

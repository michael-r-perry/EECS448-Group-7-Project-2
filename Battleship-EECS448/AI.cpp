#include "AI.h"
#include <stdlib.h>
#include <tuple>

AI::AI()
{
    m_difficulty = 'E'; // Default value
    m_randomShoot = true;
    m_searching = false;
}

void setDifficulty(char difficulty)
{
    if ((difficulty == 'E' || difficulty == 'M') || difficulty == 'H')
    {
        m_difficulty = difficulty;
    }
}

char AI::selectOrientation()
{
    int num = rand() % 2;
    if (num == 0) 
    {
        return 'h';
    }
    else 
    {
        return 'v';
    }
}

std::tuple<int, int> AI::placeShip(char orientation)
{
  int row = rand() % 9;
  int col = rand() % 10;
  return make_tuple(row, col);
}

std::tuple<int, int> AI::Shoot()
{
  std::tuple<int, int> coordinates;
  return(coordinates);
}

std::tuple<int, int> AI::easyShoot()
{

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

}

std::tuple<int, int> AI::hardShoot()
{
  rowMark = 1;
  colMark = 1;
  coordinates = hardShootHelper();
  (value at coordinates) = 'H';
}

std::tuple<int, int> AI::hardShootHelper()
{
  std::tuple<int, int> coordinates; 
  
  if(value at coordinate == 'S'){

    return(coordinates<rowMark, colMark>);
  }
  else{

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
}
#include "AI.h"
#include <stdlib.h>

char selectOrientation()
{
  int num = rand() % 2;
  if (num == 0) 
  {
    return 'H';
  }
  else 
  {
    return 'V';
  }
}

std::tuple<int, int> place Ship(char orientation)
{
  std::tuple<int, int> coordinates;
  return(coordinates);
}

std::tuple<int, int> Shoot()
{
  std::tuple<int, int> coordinates;
  return(coordinates);
}

void easyShoot()
{

}

void mediumShoot()
{

}

void hardShoot()
{
  rowMark = 1;
  colMark = 1;
  coordinates = hardShootHelper();
  (value at coordinates) = 'H';
}

std::tuple hardShootHelper()
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
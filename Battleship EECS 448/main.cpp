#include "DisplayBoard.h"
#include <iostream>; 
using namespace std;

int main()
{
	DisplayBoard exec;
	exec.Init();
	exec.ShowBoard();
	exec.NumOfShips();
	return(0);
}
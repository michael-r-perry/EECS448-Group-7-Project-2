#include "DisplayBoard.h"
#include "ShipBoard.h"
#include <iostream>
using namespace std;

int main()
{
	DisplayBoard exec;
	exec.ShowBoard();
	exec.NumOfShipsPrompt();
	return(0);
}
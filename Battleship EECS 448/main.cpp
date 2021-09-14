#include "DisplayBoard.h"
#include "ShipBoard.h"
#include <iostream>
using namespace std;

int main()
{
	DisplayBoard exec;
	exec.Init();
	exec.ShowBoard();
	exec.NumOfShipsPrompt();
	return(0);
}
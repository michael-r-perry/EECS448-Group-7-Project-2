#include "ShipDriver.h"
#include <iostream>
#include <string>
#include <stdlib.h>
using namespace std;

void Clear()
{
    #if __APPLE__
        system("clear");
    #elif _WIN32
        system("cls");
    #else
        system("cls"):
    #endif
}

int main()
{
	srand(time(NULL)); // Set random seed
	
	int choice = 0;

	do
	{
		cout << "1.) Start Game\n"; // Display menu
		cout << "2.) Quit\n";
		cout << "Enter choice: ";
		cin >> choice;

		/*
		* Code courtesy of Doug T. at https://stackoverflow.com/questions/5864540/infinite-loop-with-cin-when-typing-string-while-a-number-is-expected
		*/
		if (cin.fail()) // If user has a bad input i.e. char 
		{
			cin.clear(); // get rid of failure state
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discards bad character

			Clear();
			cout << "Invalid choice!\n";
			system("pause");
			Clear();
		}
		else if (choice == 1)
		{
			Clear();
			ShipDriver driver;
		}
		else if (choice != 2)
		{
			Clear();
			cout << "Invalid choice!\n";
			system("pause");
			Clear();
		}
	} while (choice != 2);
	
	return(0);
}


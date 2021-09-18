#include "ShipDriver.h"
#include "ShipDriver.cpp"
#include <iostream>
using namespace std;

int main()
{
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

			system("cls");
			cout << "Invalid choice!\n";
			system("pause");
			system("cls");
		}
		else if (choice == 1)
		{
			system("cls");
			ShipDriver driver;
		}
		else if (choice != 2)
		{
			system("cls");
			cout << "Invalid choice!\n";
			system("pause");
			system("cls");
		}
	} while (choice != 2);
	
	return(0);
}
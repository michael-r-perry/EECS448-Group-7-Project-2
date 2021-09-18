BattleShip: main.o ShipDriver.o ShipBoard.o DisplayBoard.o
	g++ -g -std=c++11 -Wall main.o ShipDriver.o ShipBoard.o DisplayBoard.o -o BattleShip

main.o: main.cpp ShipDriver.h
	g++ -g -std=c++11 -Wall -c main.cpp

ShipDriver.o: ShipDriver.h ShipDriver.cpp ShipBoard.h DisplayBoard.h
	g++ -g -std=c++11 -Wall -c ShipDriver.cpp

ShipBoard.o: ShipBoard.h ShipBoard.cpp
	g++ -g -std=c++11 -Wall -c ShipBoard.cpp

DisplayBoard.o: DisplayBoard.h DisplayBoard.cpp ShipBoard.h
	g++ -g -std=c++11 -Wall -c DisplayBoard.cpp

clean:
	rm *.o BattleShip

game: main.o Arena.o Game.o Player.o Robot.o utilities.o
	g++ main.o Arena.o Game.o Player.o Robot.o utilities.o -o game

main.o: main.cpp
	g++ -c main.cpp

Arena.o: Arena.cpp Arena.h
	g++ -c Arena.cpp

Game.o: Game.cpp Game.h
	g++ -c Game.cpp

Player.o: Player.cpp Player.h
	g++ -c Player.cpp

Robot.o: Robot.cpp Robot.h
	g++ -c Robot.cpp

utilities.o: utilities.cpp
	g++ -c utilities.cpp

clean:
	rm *.o game

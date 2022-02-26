all: game tests

game: cards.cpp cards.h main.cpp
	g++ --std=c++11 -Wall cards.cpp main.cpp -o game

tests: tests.cpp cards.h cards.cpp
	g++ --std=c++11 -Wall cards.cpp tests.cpp -o tests

clean:
	rm game
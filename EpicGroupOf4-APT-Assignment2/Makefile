.default: all

all: qwirkle

clean:
	rm -rf qwirkle *.o *.dSYM


qwirkle: Tile.o Node.o LinkedList.o qwirkle.o Player.o Game.o Board.o UserMenu.o TileBag.o Util.o
	g++ -Wall -Werror -std=c++14 -g -O -o $@ $^

%.o: %.cpp
	g++ -Wall -Werror -std=c++14 -g -O -c $^

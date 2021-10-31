CC = g++
CFLAGS = -g -Wall --std=c++17

ODIR = build

SRC = $(wildcard test/*.cpp)
OBJ = $(src:.cpp=.o)

all: sfml sfml-build

sfml: src/main.cpp src/game.cpp src/World.cpp src/Node.cpp
	$(CC) $(CFLAGS) -c src/main.cpp src/game.cpp src/World.cpp src/Node.cpp


# to compile all files
# sfml: $(SRC)
# 	$(CC) $(CFLAGS) -c $(SRC)


sfml-build: main.o game.o World.o Node.o
		$(CC) main.o game.o World.o Node.o -o out -lsfml-graphics -lsfml-window -lsfml-system

.PHONY: clean

clean:
	rm -rf *.o out sfml

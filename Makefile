CC = g++
CFLAGS = -g -Wall -Wno-switch --std=c++17

ifeq ($(OS),Windows_NT)
	# Windows specific definitions
	# NOTE: Change these paths to appropriate libs subdirectories after SMFL library (Windows version) is checked in into libs
	# NB! Must be revised for general use (in case the project will be used by any Windows users)
	IFLAGS = -IC:\Users\Niko\git\SFML-test\SFML-2.5.1-windows-gcc-7.3.0-mingw-32-bit\SFML-2.5.1\include
	LFLAGS = -LC:\Users\Niko\git\SFML-test\SFML-2.5.1-windows-gcc-7.3.0-mingw-32-bit\SFML-2.5.1\lib
	TARGET = out.exe
	DELETE = del /Q /S
else
	# Linux specific definitions
	TARGET = out
	DELETE = rm -rf
endif

# NB! Use this option once all the files are implemented. Using it before then
# causes numerous compilation and linker erros
SRC = $(wildcard test/*.cpp)
OBJ = $(src:.cpp=.o)

all: sfml sfml-build

sfml: src/main.cpp src/game.cpp src/World.cpp src/Node.cpp src/Mode.cpp src/MainMenu.cpp src/BackgroundSprite.cpp
	$(CC) $(CFLAGS) $(IFLAGS) -c src/main.cpp src/game.cpp src/World.cpp src/Node.cpp src/Mode.cpp src/MainMenu.cpp src/BackgroundSprite.cpp


# to compile all files
# sfml: $(SRC)
# 	$(CC) $(CFLAGS) -c $(SRC)

sfml-build: main.o game.o World.o Node.o Mode.o MainMenu.o BackgroundSprite.o
		$(CC) main.o game.o World.o Node.o Mode.o MainMenu.o BackgroundSprite.o -o $(TARGET) $(LFLAGS) -lsfml-graphics -lsfml-window -lsfml-system

.PHONY: clean

clean:
	$(DELETE) *.o $(TARGET) sfml

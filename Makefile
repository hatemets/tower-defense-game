CC = g++
CFLAGS = -g -Wall -Wno-switch --std=c++17

TARGET := sfml
OBJ_DIR := ./obj
SRC_DIR := ./src
SRC_FILES := $(shell find $(SRC_DIR) -type f -name *.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%,$(OBJ_DIR)/%,$(SRC_FILES:.cpp=.o))
LIBS = -lsfml-graphics -lsfml-window -lsfml-system

ifeq ($(OS),Windows_NT)
	# Windows specific definitions
	# NOTE: Change these paths to appropriate libs subdirectories after SMFL library (Windows version) is checked in into libs
	# NB! Must be revised for general use (in case the project will be used by any Windows users)
	IFLAGS = -IC:\Users\Niko\git\SFML-test\SFML-2.5.1-windows-gcc-7.3.0-mingw-32-bit\SFML-2.5.1\include
	LFLAGS = -LC:\Users\Niko\git\SFML-test\SFML-2.5.1-windows-gcc-7.3.0-mingw-32-bit\SFML-2.5.1\lib
	OUT_FILE = out.exe
	DELETE = del /Q /S
else
	# Linux specific definitions
	OUT_FILE = out
	DELETE = rm -rf
endif

all: $(TARGET)

# Link
$(TARGET): $(OBJ_FILES) 
	$(CC) -o $(OUT_FILE) $^ $(LIBS)

# Compile
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(IFLAGS) -c -o $@ $<

.PHONY: clean

clean:
	$(DELETE) $(OBJ_DIR)/*.o $(TARGET)

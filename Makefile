CC = g++
CFLAGS = -g -Wall -Wno-switch --std=c++17

TARGET := out
OBJ_DIR := ./obj
SRC_DIR := ./src
HEADER_DIR := ./include
LIBS = -lsfml-graphics -lsfml-window -lsfml-system

ifeq ($(OS),Windows_NT)
	# Windows specific definitions
	# NOTE: Change these paths to appropriate libs subdirectories after SMFL library (Windows version) is checked in into libs
	# NB! Must be revised for general use (in case the project will be used by any Windows users)
	IFLAGS = -IC:\Users\Niko\git\SFML-test\SFML-2.5.1-windows-gcc-7.3.0-mingw-32-bit\SFML-2.5.1\include
	LFLAGS = -LC:\Users\Niko\git\SFML-test\SFML-2.5.1-windows-gcc-7.3.0-mingw-32-bit\SFML-2.5.1\lib
	OUT_FILE = out.exe
	TARGET = $(OUT_FILE)
	CLEAN = del /Q .\obj\*.o $(OUT_FILE)
	MKDIR_OBJ = -@if not exist .\obj mkdir .\obj

# these wildcard commands should work also in Linux
	SRC_FILES := $(wildcard ./src/*.cpp)
	CONST_FILES := $(wildcard ./include/auxiliary/*.hpp)
	HPP_FILES := $(wildcard ./include/*.hpp)
else
	# Linux specific definitions
	OUT_FILE = out
	CLEAN = rm -rf $(OBJ_DIR)*/.o $(TARGET)
	MKDIR_OBJ = @mkdir -p $(OBJ_DIR)
	SRC_FILES := $(shell find $(SRC_DIR) -type f -name *.cpp)
	OBJ_FILES := $(patsubst $(SRC_DIR)/%,$(OBJ_DIR)/%,$(SRC_FILES:.cpp=.o))
	CONST_FILES := $(shell find $(HEADER_DIR)/auxiliary/ -type f -name *.hpp)
	HPP_FILES := $(shell find $(HEADER_DIR) -type f -name *.hpp)
endif

OBJ_FILES := $(patsubst $(SRC_DIR)/%,$(OBJ_DIR)/%,$(SRC_FILES:.cpp=.o))

all: $(TARGET)

# Link
$(TARGET): $(OBJ_FILES)
	$(CC) -o $(OUT_FILE) $(LFLAGS) $^ $(LIBS)

# Compile
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(HPP_FILES) $(CONST_FILES)
	$(MKDIR_OBJ)
	$(CC) $(CFLAGS) $(IFLAGS) -c -o $@ $<

.PHONY: clean

clean:
	$(CLEAN)

CC = g++
CFLAGS = -g -Wall -Wno-switch --std=c++17

TARGET := out
OBJ_DIR := ./obj
SRC_DIR := ./src
HEADER_DIR := ./include

LIBS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

ifeq ($(OS),Windows_NT)
	# Windows specific definitions
	IFLAGS = -I.\libs\windows\SFML-2.5.1\include
	LFLAGS = -L.\libs\windows\SFML-2.5.1\lib
	SRC_FILES := $(wildcard ./src/*.cpp)
	CONST_FILES := $(wildcard ./include/auxiliary/*.hpp)
	HPP_FILES := $(wildcard ./include/*.hpp)
	OUT_FILE = out.exe
	TARGET = $(OUT_FILE)
	CLEAN = del /Q .\obj\*.o $(TARGET)
	MKDIR_OBJ = -@if not exist .\obj mkdir .\obj
else
	# Linux specific definitions
	IFLAGS = -I ./libs/linux
	LFLAGS = -L ./libs/linux/sfml-libs
	SRC_FILES := $(shell find $(SRC_DIR) -type f -name *.cpp)
	CONST_FILES := $(shell find $(HEADER_DIR)/auxiliary/ -type f -name *.hpp)
	HEADER_FILES := $(shell find $(HEADER_DIR) -type f -name *.hpp)
	OUT_FILE = out
	CLEAN = rm -rf $(OBJ_DIR)/*.o $(TARGET)
	MKDIR_OBJ = @mkdir -p $(OBJ_DIR)
endif

OBJ_FILES := $(patsubst $(SRC_DIR)/%,$(OBJ_DIR)/%,$(SRC_FILES:.cpp=.o))

all: $(TARGET)

# Link
$(TARGET): $(OBJ_FILES)
	$(CC) -o $(OUT_FILE) $(LFLAGS) $^ $(LIBS)

# Compile
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(HPP_FILES)
	$(MKDIR_OBJ)
	$(CC) $(CFLAGS) $(IFLAGS) -c -o $@ $<

.PHONY: clean

clean:
	$(CLEAN)

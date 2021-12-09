CC = g++
CFLAGS = -g -Wall -Wno-switch --std=c++17

TARGET := out
TEST_TARGET := test
OBJ_DIR := ./obj
SRC_DIR := ./src
TEST_DIR := ./tests
HEADER_DIR := ./include

ifeq ($(OS),Windows_NT)
	# Windows specific definitions
	LIBS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
	IFLAGS = -I.\libs\windows\SFML-2.5.1\include
	LFLAGS = -L.\libs\windows\SFML-2.5.1\lib
	SRC_FILES := $(wildcard ./src/*.cpp)
	CONST_FILES := $(wildcard ./include/auxiliary/*.hpp)
	HPP_FILES := $(wildcard ./include/*.hpp)
	OUT_FILE = out.exe
	TARGET = $(OUT_FILE)
	CLEAN = del /Q .\obj\*.o $(TARGET)
	MKDIR_OBJ = -@if not exist .\obj mkdir .\obj
	RUN_COMMAND = ./$(TARGET)
else
	# Linux specific definitions
	LIBS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
	LIB_SOURCE = "./libs/linux/lib"
	IFLAGS = -I ./libs/linux
	LFLAGS = -L $(LIB_SOURCE)
	SRC_FILES := $(shell find $(SRC_DIR) -type f -name *.cpp)
	CONST_FILES := $(shell find $(HEADER_DIR)/auxiliary/ -type f -name *.hpp)
	HEADER_FILES := $(shell find $(HEADER_DIR) -type f -name *.hpp)
	OUT_FILE = out
	CLEAN = rm -rf $(OBJ_DIR)/*.o $(TARGET) $(TEST_TARGET)
	MKDIR_OBJ = @mkdir -p $(OBJ_DIR)
	RUN_COMMAND = LD_LIBRARY_PATH=$(LIB_SOURCE) ./$(TARGET)
	TEST_FILES := $(shell find $(TEST_DIR) -type f -name *.cpp)
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

run: $(TARGET)
	$(RUN_COMMAND)


# NOTE: Testing is only available on Linux
test: 
	$(CC) $(CFLAGS) $(TEST_DIR)/*.cpp -o $(TEST_TARGET)

.PHONY: clean

clean:
	$(CLEAN)

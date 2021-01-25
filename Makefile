#DEBUG_FLAGS = -O0 -g -Wall
DEBUG_FLAGS = -O0 -g
PERF_FLAGS = -O3

CC = g++
CXXFLAGS = -std=c++17

TARGET = aoc2015.exe
OBJ_DIR = ./obj
DEPS = src/*.h \
	   src/*.hpp
#SRC = $(wildcard src/*.cpp)
SRC = src/*.cpp

$(TARGET): $(SRC) $(DEPS)
	$(CC) $(CXXFLAGS) $(DEBUG_FLAGS) -o $(TARGET) $(SRC)

.PHONY: clean

all:  $(TARGET)

release:
	$(CC) $(CXXFLAGS) $(PERF_FLAGS) -o $(TARGET) $(SRC)

clean:
	-$(RM) -f $(OBJ_DIR)/*.obj *.obj *.exe *.ilk *.pdb
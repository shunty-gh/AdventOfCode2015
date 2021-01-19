#DEBUG_FLAGS = -O0 -g -Wall
DEBUG_FLAGS = -O0 -g

PERF_FLAGS = -O3

CC = g++
CPP_FLAGS = -std=c++17

TARGET = aoc2015.exe

all:  $(TARGET)

$(TARGET): src/main.cpp src/*.cpp
	$(CC) $(CPP_FLAGS) $(DEBUG_FLAGS) -o $(TARGET) src/*.cpp

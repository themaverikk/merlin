CXX=clang++
CXXFLAGS=-g -std=c++17

SRC=$(wildcard *.cpp)
OBJ=$(SRC:%.cpp=%.o)
current_dir=$(shell pwd)

%.o: %.cpp
	@$(CXX) $(CXXFLAGS) $< -o $(current_dir)/out/$@

all: createOutputDir $(OBJ) 
	@tput setaf 2; echo "BUILD COMPLETE."

createOutputDir:
	@if [ ! -d $(current_dir)/out ]; then  mkdir $(current_dir)/out;fi

clean:
	@rm -rf out/*
	@tput setaf 2; echo "CLEANING COMPLETE."

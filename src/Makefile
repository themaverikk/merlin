CXX=clang++
CXXFLAGS=-g -std=c++17

SRC=$(wildcard *.cpp)
OBJ=$(SRC:%.cpp=%.o)
current_dir=$(shell pwd)

%.o: %.cpp
	@$(CXX) $(CXXFLAGS)  -c $< -o $(current_dir)/out/$@

all: createOutputDir $(OBJ) 
	@tput setaf 2; echo "BUILD COMPLETE."

createOutputDir:
	@if [ ! -d $(current_dir)/out ]; then  mkdir $(current_dir)/out;fi

clean:
	rm -f out/*.o

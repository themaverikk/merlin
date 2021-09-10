CXX=clang++
CXXFLAGS=-g -std=c++17

SRC=$(wildcard *.cpp)
OBJ=$(SRC:%.cpp=%.o)
current_dir=$(shell pwd)

%.o: %.cpp
	@$(CXX) $(CXXFLAGS)  -c $< -o $(current_dir)/out/$@

all: $(OBJ)
	@tput setaf 2; echo "BUILD COMPLETE."

clean:
	rm -f bin/*.o

CXX=clang++
CXXFLAGS=-g -std=c++17

SRC=$(wildcard *.cpp)
OBJ=$(SRC:%.cpp=%.o)


%.o: %.c
	$(CXX) $@ -c $< $(CXXFLAGS)

all: $(OBJ)
	$(CXX) -o $^ $(CXXFLAGS)


clean:
	rm -f *.o

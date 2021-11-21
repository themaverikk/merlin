CXX=clang++
CXXFLAGS=-std=c++17

SRC=$(wildcard *.cpp)
OBJ=$(SRC:%.cpp=%.o)
current_dir=$(shell pwd)

%.o: %.cpp
	@$(CXX) $(CXXFLAGS) $< -o $(current_dir)/out/$@

merlin : clean
	@$(CXX) $(CXXFLAGS) merlin.cpp FunctionDefinition.cpp Tokenizer.cpp Parser.cpp Statement.cpp Interpreter.cpp Variable.cpp -o merlin
	@tput setaf 2; echo "BUILD COMPLETE.";tput sgr0
	@echo "Run the merlin executable with the mn file as argument . i.e. ./merlin test.mn"
all: createOutputDir $(OBJ) 
	@tput setaf 2; echo "BUILD COMPLETE.";tput sgr0

createOutputDir:
	@if [ ! -d $(current_dir)/out ]; then  mkdir $(current_dir)/out;fi

clean:
	@tput setaf 2; echo "CLEANING PRECOMPILED FILES.";tput sgr0
	-@rm -rf out/*
	-@rm merlin
	@tput setaf 2; echo "CLEANING COMPLETE.";tput sgr0

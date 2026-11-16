CXX ?= g++
CXXFLAGS := -std=c++17 -Wall -Wextra -pedantic -Iinclude
CORE := src/Expression.cpp src/Parentheses.cpp

ifeq ($(OS),Windows_NT)
    EXE := .exe
    RUN := .\\
    RM := del /Q /F
else
    EXE :=
    RUN := ./
    RM := rm -f
endif

all: expr_eval$(EXE)

expr_eval$(EXE): src/main.cpp $(CORE) include/Stack.h include/Expression.h include/Parentheses.h
	$(CXX) $(CXXFLAGS) src/main.cpp $(CORE) -o expr_eval$(EXE)

test_runner$(EXE): tests/test_main.cpp $(CORE) include/Stack.h include/Expression.h include/Parentheses.h
	$(CXX) $(CXXFLAGS) tests/test_main.cpp $(CORE) -o test_runner$(EXE)

test: test_runner$(EXE)
	$(RUN)test_runner$(EXE)

clean:
	$(RM) expr_eval$(EXE) test_runner$(EXE)


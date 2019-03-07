CXX ?= g++
CXXFLAGS = -I../src -std=c++14 -Wextra -Wpedantic -Wall -O3 -DDEBUG
LDLIBS = -L../lib/ -lvroom -lboost_system -lpthread

MAIN = ./test
SRC = test.cpp util.cpp debug.cpp

main : $(MAIN)

$(MAIN) : $(SRC)
	$(CXX) $(CXXFLAGS) $^ $(LDLIBS) -o $@

clean :
	$(RM) $(MAIN)

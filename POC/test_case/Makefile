CXX ?= g++
CXXFLAGS = -I../../OSRM/Vroom/vroom-1.3.0/src -std=c++14 -Wextra -Wpedantic -Wall -O3 -DDBUG
LDLIBS = -L../../OSRM/Vroom/vroom-1.3.0/lib/ -lvroom -lboost_system -lpthread -lcurl

MAIN = ./test
SRC = test.cpp util.cpp debug.cpp

main : $(MAIN)

$(MAIN) : $(SRC)
	$(CXX) $(CXXFLAGS) $^ $(LDLIBS) -o $@

clean :
	$(RM) $(MAIN)

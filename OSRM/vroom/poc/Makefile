CXX ?= g++
CXXFLAGS = -I../src -std=c++14 -Wextra -Wpedantic -Wall -O3
CXXFLAGS += -I/usr/local/opt/curl/include/curl/

LDLIBS = -L../lib/ -lvroom -lboost_system -lpthread
LDLIBS += -L/usr/local/opt/curl/lib

MAIN = ./poc
SRC = poc.cpp

all : $(MAIN)

$(MAIN) : $(SRC)
	$(CXX) $(CXXFLAGS) $^ $(LDLIBS) -o $@

clean :
	$(RM) $(MAIN)

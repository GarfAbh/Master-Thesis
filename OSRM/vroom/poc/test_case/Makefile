CXX ?= g++
CXXFLAGS = -I../../src -std=c++14 -Wextra -Wpedantic -Wall -O3
LDLIBS = -L../../lib/ -lvroom -lboost_system -lpthread -lcurl

sources = util.cpp main.cpp
header = util.h
objets = $(sources:.cpp=.o)

%: %.o
	$(LINK.cc) -o $@ $^

test : $(objets)

clean :
	rm -f *.o *.bak

mrproper : clean
	rm -f test

depend :
	makedepend $(sources)

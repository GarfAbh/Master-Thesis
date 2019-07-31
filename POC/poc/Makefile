CXX ?= g++
CXXFLAGS = -I../../OSRM/Vroom/vroom-1.3.0/src -std=c++14 -Wextra -Wpedantic -Wall -O3
LDLIBS = -L../../OSRM/Vroom/vroom-1.3.0/lib/ -lvroom -lboost_system -lpthread -lcurl

MAIN = ./poc
SRC = poc.cpp

QUAL = ./qual
QUAL_SRC = qualitatif.cpp

main : $(MAIN)

$(MAIN) : $(SRC)
	$(CXX) $(CXXFLAGS) $^ $(LDLIBS) -o $@

qual : $(QUAL)

$(QUAL) : $(QUAL_SRC)
	$(CXX) $(CXXFLAGS) $^ $(LDLIBS) -o $@

clean :
	$(RM) $(MAIN)

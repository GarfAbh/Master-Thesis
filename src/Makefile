C = gcc
CFLAGS += -g
CFLAGS += -std=c++11
CFLAGS += -Wall
CFLAGS += -Werror
IDIR = -I/../OSRM/osrm-backend/include


all : osrm-test

osrm-test: osrm-test.cpp

.PHONY: clean

clean :
	rm -rf *.o

mrproper : clean
	rm-rf osrm-test

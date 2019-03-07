#!/usr/bin/env bash

cd ..

# dependancies instalation :
sudo apt install build-essential git cmake pkg-config \
libbz2-dev libxml2-dev libzip-dev libboost-all-dev \
lua5.2 liblua5.2-dev libtbb-dev

#build the backend
cd OSRM/osrm-backend

#TODO probably find a way to test if the build has already been done or not.
mkdir build
cd build
cmake ..
cmake --build .
sudo cmake --build . --target install
cd ..

#build the example executable
#same here
mkdir example-1
cd example-1
cmake . ../example/
make osrm-example
cd ../../..

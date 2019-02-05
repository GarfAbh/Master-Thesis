#!/usr/bin/env bash

# dependancies instalation :
sudo apt install build-essential git cmake pkg-config \
libbz2-dev libxml2-dev libzip-dev libboost-all-dev \
lua5.2 liblua5.2-dev libtbb-dev

#create and fill up the data folder with the data needed for the example
# il faudrais faire en sorte que ce soit si ca existe pas déjà
if [ -e data/monaco/monaco-latest.osm.pbf ]; then
  echo needed data and folder already exist.
else
  echo data folder creation + fil it up with the monaco data from geofabrik
  mkdir data/monaco
  cd data/monaco
  wget http://download.geofabrik.de/europe/monaco-latest.osm.pbf
  cd ../..
fi

#build the system
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

#preprocess the data
./OSRM/osrm-backend/build/osrm-extract data/monaco/monaco-latest.osm.pbf -p \
OSRM/osrm-backend/profiles/car.lua
./OSRM/osrm-backend/build/osrm-partition data/monaco/monaco-latest.osrm
./OSRM/osrm-backend/build/osrm-customize data/monaco/monaco-latest.osrm

#run the example
echo
echo example runs and output is : ==============================================
echo
./OSRM/osrm-backend/example-1/osrm-example data/monaco/monaco-latest.osrm
echo

#!/usr/bin/env bash

# The idea here is only to copy past some usefull commande and comment it in
# order to prepare a huge and beautifull instalation script

#instalation des dependance

sudo apt install build-essential git cmake pkg-config \
libbz2-dev libxml2-dev libzip-dev libboost-all-dev \
lua5.2 liblua5.2-dev libtbb-dev

#instalation du repo complet
git clone ...

#creation du folder data

mkdir

#build l'entier du system

mkdir -p build
cd build
cmake ..
cmake --build .
sudo cmake --build . --target install


#preprocess des data.
wget http://download.geofabrik.de/europe/germany/berlin-latest.osm.pbf

osrm-extract path/to/my-map.osm.pbf -p path/to/car.lua
osrm-partition berlin.osrm
osrm-customize berlin.osrm

osrm-routed --algorithm=MLD berlin.osrm

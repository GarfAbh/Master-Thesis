#!/usr/bin/env bash

cd ..

if [ ! -e data/ ]; then
  echo creation of data folder
  mkdir data
fi

if [ ! -e data/OSM ]; then
  echo creation of data folder for OSM file
  mkdir data/OSM
fi


if [ ! -e data/OSRM ]; then
  echo creation of data folder for OSRM file
  mkdir data/OSRM
fi

if [ ! -e data/GraphHopper ]; then
  echo creation of data folder for GraphHopper file
  mkdir data/GraphHopper
fi

if [ ! -e data/OSM/switzerland ]; then
  echo creation of swiss for OSM
  wget http://download.geofabrik.de/europe/switzerland-latest.osm.pbf
  mkdir data/OSM/switzerland
fi


if [ ! -e data/OSRM/switzerland ]; then
  mkdir data/OSRM/switzerland
  echo creation of swiss for OSRM
  cp switzerland.geojson data/OSRM/switzerland
  ./OSRM/osrm-backend/build/osrm-extract data/OSM/switzerland/switzerland-latest.osm.pbf \
  -p OSRM/osrm-backend/profiles/car.lua --location-dependent-data=../data/OSRM/switzerland/switzerland.geojson
  mv data/OSM/switzerland/switzerland-latest.osrm* data/OSRM/switzerland
fi

#TODO figure out how does the map are treated by graphhopper ...
if [ ! -e data/GraphHopper/switzerland ]; then
  echo creation of swiss for graphopper
  mkdir data/GraphHopper/switzerland
fi

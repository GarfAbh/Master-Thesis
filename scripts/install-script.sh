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

if [ ! -e data/OSM/switzerland ]; then
  echo creation of swiss for OSM
  mkdir data/OSM/switzerland
  cd data/OSM/switzerland
  wget http://download.geofabrik.de/europe/switzerland-latest.osm.pbf
  cd ../../..
fi


if [ ! -e data/OSRM/switzerland ]; then

  echo creation of swiss for OSRM
  mkdir data/OSRM/switzerland
  cd data/OSRM/switzerland
  wget https://github.com/ZHB/switzerland-geojson/blob/master/country/switzerland.geojson
  cd ../../..
  ./OSRM/osrm-backend/build/osrm-extract data/OSM/switzerland/switzerland-latest.osm.pbf \
  -p OSRM/osrm-backend/profiles/car.lua --location-dependent-data=../data/OSRM/switzerland/switzerland.geojson
  mv data/OSM/switzerland/switzerland-latest.osrm* data/OSRM/switzerland
fi

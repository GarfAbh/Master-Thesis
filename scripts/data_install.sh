#!/usr/bin/env bash
#
# Download the needed data :
# Swiss address from confederation
# Map from geofabrik
# Extract what is needed from the map for OSRM

PATH_TO_DATA=$(awk -F= '$1=="PATH_TO_DATA"{print $2;exit}' ../config.txt)
PATH_TO_EXEC=$(awk -F= '$1=="PATH_TO_EXEC"{print $2;exit}' ../config.txt)

mkdir -p "$PATH_TO_DATA"
cd $PATH_TO_DATA
# create OSM in data folder if not existant
mkdir -p "$PATH_TO_DATA/OSM"
mkdir -p "$PATH_TO_DATA/Addr"
mkdir -p "$PATH_TO_DATA/OSRM"
mkdir -p "$PATH_TO_DATA/OSRM/switzerland"

cd $PATH_TO_DATA/Addr
wget https://data.geo.admin.ch/ch.bfs.gebaeude_wohnungs_register/CSV/CH/CH.zip
unzip CH.zip
rm CH.zip

cd $PATH_TO_DATA/OSM
wget http://download.geofabrik.de/europe/switzerland-latest.osm.pbf

cd $PATH_TO_DATA/OSRM/switzerland
wget https://github.com/ZHB/switzerland-geojson/archive/master.zip
unzip master.zip
rm master.zip
mv switzerland-geojson-master/country/switzerland.geojson ./switzerland.geojson
rm -r switzerland-geojson-master
wget http://download.geofabrik.de/europe/switzerland-latest.osm.pbf
$PATH_TO_EXEC/osrm-extract ./switzerland-latest.osm.pbf \
-p $PATH_TO_EXEC/profiles/car.lua --location-dependent-data=switzerland.geojson
rm switzerland-latest.osm.pbf

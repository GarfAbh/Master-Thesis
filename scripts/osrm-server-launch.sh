#!/usr/bin/env bash
cd ..

if [ "$1" != "MLD" || "$1" != "CH" ]; then
  echo usage :
  echo ./osrm-server-launch.sh [option]
  echo [option] = MLD or CH
  echo MLD = multiple level Dijkstra algorithms
  echo CH = COntraction Hierarchy
fi

./OSRM/osrm-backend/build/osrm-partition data/OSRM/switzerland/switzerland-latest.osrm
./OSRM/osrm-backend/build/osrm-customize data/OSRM/switzerland/switzerland-latest.osrm

if [ "$1" == "MLD" ]; then
  echo running osrm using multiple level Dijkstra algorithm
  ./OSRM/osrm-backend/build/osrm-routed --algorithm=MLD data/OSRM/switzerland/switzerland-latest.osrm
elif [ "$1" == "CH" ]; then
  echo running osrm using contraction hierarchy
  ./OSRM/osrm-backend/build/osrm-contract data/OSRM/switzerland/switzerland-latest.osrm
  ./OSRM/osrm-backend/build/osrm-routed --algorithm=CH data/OSRM/switzerland/switzerland-latest.osrm
else
  echo impossible
fi

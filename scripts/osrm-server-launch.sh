#!/usr/bin/env bash
#
# Launch the osrm local server.

PATH_TO_DATA=$(awk -F= '$1=="PATH_TO_DATA"{print $2;exit}' ../config.txt)
PATH_TO_EXEC=$(awk -F= '$1=="PATH_TO_EXEC"{print $2;exit}' ../config.txt)
OSRM_PORT=$(awk -F= '$1=="OSRM_PORT"{print $2;exit}' ../config.txt)

if [ $# -ne 1 ]; then
  echo usage :
  echo ./osrm-server-launch.sh [option] [port]
  echo [option] = MLD or CH
  echo MLD = multiple level Dijkstra algorithms
  echo CH = Contraction Hierarchy
  exit -1
fi

if [ "$1" == "MLD" ]; then
  echo running osrm using multiple level Dijkstra algorithm
  $PATH_TO_EXEC/osrm-partition $PATH_TO_DATA/OSRM/switzerland/switzerland-latest.osrm
  $PATH_TO_EXEC/osrm-customize $PATH_TO_DATA/OSRM/switzerland/switzerland-latest.osrm
  $PATH_TO_EXEC/osrm-routed --algorithm=MLD --port $OSRM_PORT $PATH_TO_DATA/OSRM/switzerland/switzerland-latest.osrm
elif [ "$1" == "CH" ]; then
  echo running osrm using contraction hierarchy
  $PATH_TO_EXEC/osrm-contract $PATH_TO_DATA/OSRM/switzerland/switzerland-latest.osrm
  $PATH_TO_EXEC/osrm-routed --algorithm=CH --port $OSRM_PORT $PATH_TO_DATA/OSRM/switzerland/switzerland-latest.osrm
else
  echo usage :
  echo ./osrm-server-launch.sh [option] [port]
  echo [option] = MLD or CH
  echo MLD = multiple level Dijkstra algorithms
  echo CH = Contraction Hierarchy
  exit -1
fi

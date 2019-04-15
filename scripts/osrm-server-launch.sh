#!/usr/bin/env bash
#
# Launch the osrm local server.

PATH_TO_DATA=$(awk -F= '$1=="PATH_TO_DATA"{print $2;exit}' ../config.txt)
PATH_TO_EXEC=$(awk -F= '$1=="PATH_TO_EXEC"{print $2;exit}' ../config.txt)
BUILD="$PATH_TO_EXEC/osrm/osrm-backend-5.22.0/build"

if [ $# -eq 0 || $# -eq 1 ]; then
  echo usage :
  echo ./osrm-server-launch.sh [option] [port]
  echo [option] = MLD or CH
  echo [port] = i.e 5001 server port to listen
  echo MLD = multiple level Dijkstra algorithms
  echo CH = Contraction Hierarchy
  exit -1
fi

if [ "$1" == "MLD" ]; then
  echo running osrm using multiple level Dijkstra algorithm
  ${BUILD}/osrm-routed --algorithm=MLD --port ${2} $PATH_TO_DATA/OSRM/switzerland/switzerland-latest.osrm
elif [ "$1" == "CH" ]; then
  echo running osrm using contraction hierarchy
  ${BUILD}/osrm-contract ../data/OSRM/switzerland/switzerland-latest.osrm
  ${BUILD}/osrm-routed --algorithm=CH --port ${2} $PATH_TO_DATA/OSRM/switzerland/switzerland-latest.osrm
else
  echo usage :
  echo ./osrm-server-launch.sh [option] [port]
  echo [option] = MLD or CH
  echo [port] = i.e 5001 server port to listen
  echo MLD = multiple level Dijkstra algorithms
  echo CH = Contraction Hierarchy
  exit -1
fi

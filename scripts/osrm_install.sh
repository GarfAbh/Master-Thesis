#!/usr/bin/env bash
#
# Download and install osrm

PATH_TO_DATA=$(awk -F= '$1=="PATH_TO_DATA"{print $2;exit}' ../config.txt)
PATH_TO_EXEC=$(awk -F= '$1=="PATH_TO_EXEC"{print $2;exit}' ../config.txt)

mkdir -p "$PATH_TO_EXEC"
cd $PATH_TO_EXEC

#/osrm/osrm-backend-5.22.0/build

wget https://github.com/Project-OSRM/osrm-backend/archive/v5.22.0.zip -O osrm.zip
unzip osrm.zip -d ./osrm
rm osrm.zip
cd osrm/osrm-backend-5.22.0/
mkdir build
cd build
cmake ..
cmake --build .
sudo cmake --build . --target install
cd $PATH_TO_EXEC
mv osrm/osrm-backend-5.22.0/profiles .
mv osrm/osrm-backend-5.22.0/build/osrm-extract .
mv osrm/osrm-backend-5.22.0/build/osrm-partition .
mv osrm/osrm-backend-5.22.0/build/osrm-customize .
mv osrm/osrm-backend-5.22.0/build/osrm-routed .
mv osrm/osrm-backend-5.22.0/build/osrm-contract .
rm -r osrm/

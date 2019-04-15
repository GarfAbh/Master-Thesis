#!/usr/bin/env bash
#
# Download and install osrm

PATH_TO_DATA=$(awk -F= '$1=="PATH_TO_DATA"{print $2;exit}' ../config.txt)
PATH_TO_EXEC=$(awk -F= '$1=="PATH_TO_EXEC"{print $2;exit}' ../config.txt)

mkdir -p "$PATH_TO_EXEC"
cd $PATH_TO_EXEC

wget https://github.com/Project-OSRM/osrm-backend/archive/v5.22.0.zip -O osrm.zip
unzip osrm.zip -d ./osrm
rm osrm.zip
cd osrm/osrm-backend-5.22.0/
mkdir build
cd build
cmake ..
cmake --build .
sudo cmake --build . --target install

#je devrais move les executable à la source et supprimer le reste

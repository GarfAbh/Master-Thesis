#!/usr/bin/env bash
#
# Perform a full installation of tuxy road

PATH_TO_DATA=''
PATH_TO_EXEC=''
OSRM_PORT=''

echo Hi this is the script to install all that you need for TuxyRoad.
echo Please give me a path where to put the data \(map\) and swiss federal data
echo absolute path relative to this machine is better
read -p "path ? " PATH_TO_DATA
echo now give me a path where to put the executable VROOM and OSRM
echo absolute path relative to this machine is better
read -p "path ? " PATH_TO_EXEC
echo OSRM run a local instance server give me a port for the interne communication
echo it has to be a free and valid port
read -p "port ? " OSRM_PORT

echo "; config.ini" > ../config.ini
echo "[DEFAULT]" >> ../config.ini
echo "PATH_TO_DATA = $PATH_TO_DATA" >> ../config.ini
echo "PATH_TO_EXEC = $PATH_TO_EXEC" >> ../config.ini
echo "OSRM_PORT = $OSRM_PORT" >> ../config.ini

echo "PATH_TO_DATA=$PATH_TO_DATA" > ../config.txt
echo "PATH_TO_EXEC=$PATH_TO_EXEC" >> ../config.txt
echo "OSRM_PORT=$OSRM_PORT" >> ../config.txt

echo Now I\'ll download the needed package
./dependancies_install.sh

echo Now I\'ll install VROOM
./vroom_install.sh
echo path to vroom : "$PATH_TO_EXEC"/vroom

echo Now I\'ll install OSRM
./osrm_install.sh
echo path to osrm : "$PATH_TO_EXEC"/osrm

echo Now I\'ll install the data
./data_install.sh
echo path to data : "$PATH_TO_DATA"

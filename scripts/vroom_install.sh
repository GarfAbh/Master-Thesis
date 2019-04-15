#!/usr/bin/env bash
#
# Dowload and install vroom

PATH_TO_DATA=$(awk -F= '$1=="PATH_TO_DATA"{print $2;exit}' ../config.txt)
PATH_TO_EXEC=$(awk -F= '$1=="PATH_TO_EXEC"{print $2;exit}' ../config.txt)

mkdir -p "$PATH_TO_EXEC"
cd $PATH_TO_EXEC

wget https://github.com/VROOM-Project/vroom/archive/v1.4.0.zip -O vroom.zip
unzip vroom.zip -d ./vroom
rm vroom.zip
cd vroom/vroom-1.4.0/src
make

#je devrais move les executable à la source et supprimer le reste

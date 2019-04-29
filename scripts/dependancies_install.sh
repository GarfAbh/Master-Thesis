#!/usr/bin/env bash
#
# Perform and instalation of the needed dependancies and python lib

# dependancies installation
sudo apt install build-essential git cmake pkg-config \
libbz2-dev libxml2-dev libzip-dev libboost-all-dev \
lua5.2 liblua5.2-dev libtbb-dev

# python lib installation
pip install flask
pip install fuzzywuzzy
pip install pandas

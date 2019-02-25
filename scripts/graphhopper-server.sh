#!/usr/bin/env bash

cd ..

./GraphHopper/graphhopper/graphhopper.sh -a web -i ./data/GraphHopper/switzerland/switzerland-latest.osm.pbf -o swiss-gh

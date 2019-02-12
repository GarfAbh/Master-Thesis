#!/usr/bin/env bash

cd ..

./OSRM/osrm-backend/build/osrm-partition data/OSRM/france/ile-de-france-latest.osrm
./OSRM/osrm-backend/build/osrm-customize data/OSRM/france/ile-de-france-latest.osrm
./OSRM/osrm-backend/build/osrm-routed --algorithm=MLD data/OSRM/france/ile-de-france-latest.osrm

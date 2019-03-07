#!/usr/bin/env bash

make

if [ "$1" == "-debug" ]; then
  ./test -debug ../../data/OSRM/poc_test/jobs_1.csv ../../data/OSRM/poc_test/vehicle_typie1.csv output_job1
  ./test -debug ../../data/OSRM/poc_test/jobs_2.csv ../../data/OSRM/poc_test/vehicle_typie1.csv output_job2
  ./test -debug ../../data/OSRM/poc_test/jobs_3.csv ../../data/OSRM/poc_test/vehicle_typie1.csv output_job3
else
  ./test ../../data/OSRM/poc_test/jobs_1.csv ../../data/OSRM/poc_test/vehicle_typie1.csv output_job1
  ./test ../../data/OSRM/poc_test/jobs_2.csv ../../data/OSRM/poc_test/vehicle_typie1.csv output_job2
  ./test ../../data/OSRM/poc_test/jobs_3.csv ../../data/OSRM/poc_test/vehicle_typie1.csv output_job3

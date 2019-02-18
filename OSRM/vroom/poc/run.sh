#!/usr/bin/env bash

make
if [ ! -e stat.csv ]; then
  touch stat.csv
  echo -n "job n,country,random,seed,time" >> stat.csv
  echo "" >> stat.csv
fi
for i in {1..30}
do
  for ra in true false
  do
    for co in lausanne swiss
    do
      START=$(date +%s%N | cut -b1-13)
      ./poc $i 5 4 $co $ra $i
      END=$(date +%s%N | cut -b1-13)
      DIFF=$(( $END - $START ))
      echo -n $i "," $co "," $ra "," $i "," $DIFF >> stat.csv
      echo "" >> stat.csv
    done
  done
done

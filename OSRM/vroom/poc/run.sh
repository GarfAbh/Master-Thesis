#!/usr/bin/env bash

make
if [ ! -e stat.csv ]; then
  touch stat.csv
  echo -n "job n,threads,country,random,seed,time" >> stat.csv
  echo "" >> stat.csv
fi
for i in {1..30}
do
  for ra in true false
  do
    for j in {1..64}
    do
      for k in 1 2 3 4 5
      do
        START=$(date +%s%N | cut -b1-13)
        ./poc $i $k $j lausanne $ra $i
        END=$(date +%s%N | cut -b1-13)
        DIFF=$(( $END - $START ))
        echo -n $i "," $j "," $k "," $ra "," $i "," $DIFF >> stat.csv
        echo "" >> stat.csv
      done
    done
  done
done

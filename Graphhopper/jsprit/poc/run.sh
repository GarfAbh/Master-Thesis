#!/usr/bin/env bash


if [ ! -e stat.csv ]; then
  touch stat.csv
  echo -n "job n,threads,country,random,seed,time" >> stat.csv
  echo "" >> stat.csv
fi
for i in {1..30}
do
  for ra in true false
  do
    for co in lausanne swiss
    do
      for j in {1..64}
      do
        START=$(date +%s%N | cut -b1-13)
        java -jar ../classes/artifacts/poc_jar/poc.jar $i $j $co $ra $i
        END=$(date +%s%N | cut -b1-13)
        DIFF=$(( $END - $START ))
        echo -n $i "," $j "," $co "," $ra "," $i "," $DIFF >> stat.csv
        echo "" >> stat.csv
      done
    done
  done
done

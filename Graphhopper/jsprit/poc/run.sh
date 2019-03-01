#!/usr/bin/env bash


if [ ! -e stat.csv ]; then
  touch stat.csv
  echo -n "job n,threads,profondeur,random,seed,time" >> stat.csv
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
        for k in 2 4 8 16 32 64
        do
           java -jar ../classes/artifacts/poc_jar/poc.jar $i $j lausanne $ra $i $k
           echo -n $i "," $j ","$k"," $ra "," $i "," >> stat.csv
           echo "" >> stat.csv
        done
      done
    done
  done
done

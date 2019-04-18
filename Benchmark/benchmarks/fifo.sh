#!/bin/bash
. general.sh

FILE=Benchmark_1_FIFO.csv

touch $FILE

for threads in {2..2}
do
   echo -e "Downloading file with $threads threads\n" >> $FILE
   ./bclient $IP $Port $N_File $threads 1 >> $FILE 
done

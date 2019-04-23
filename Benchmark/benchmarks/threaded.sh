#!/bin/bash
. general.sh

#name of the file .csv
FILE=Benchmark_1_Threaded.csv

#Port of WebServer
Port = 8005

touch $FILE

# call the tools of Benchmark with the respective parameters
for threads in {2..2}
do
   echo -e "Downloading file with $threads threads\n" >> $FILE
   ./bclient $IP $Port $N_File $threads 1 >> $FILE 
done

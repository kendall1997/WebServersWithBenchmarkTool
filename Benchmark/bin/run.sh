#!/bin/bash

touch results2.csv

for threads in {8..16}
do
   echo -e "Downloading file with $threads threads\n" >> results2.csv
   ./bclient autogestion.metrotel.com.ar 80 speedtest/archivo10MB.zip $threads 2 >> results2.csv 
done
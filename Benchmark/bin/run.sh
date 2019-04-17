#!/bin/bash

touch results2.csv

for threads in {2..5}
do
   echo -e "Downloading file with $threads threads\n" >> results_victor_2.csv
   ./bclient autogestion.metrotel.com.ar 80 speedtest/archivo10MB.zip $threads 1 >> results_victor_2.csv 
done
#!/bin/bash

FILE=forked_test.csv

touch $FILE

for threads in {2..2}
do
   echo -e "Downloading file with $threads threads\n" >> $FILE
   ./bclient 192.168.1.111 8003 rocket.webm $threads 1 >> $FILE 
done
#!/bin/bash
. general.sh

#name of the file .csv
FILE=Benchmark_image.csv

#Parameter of amount of threads
Thread=2..4

#Parameter of amount of cycles
Cycle=2

#Name of the file to download
N_File=tigre.jpg

#Port of WebServer FIFO
Port=8001

#Port of WebServer Forked
Port3=8003

#Port of WebServer Threaded
Port5=8005

#Port of WebServer Pre-fork
Port7=8007

#Port of WebServer Pre-Threaded
Port9=8009

touch $FILE

# call the tools of Benchmark with the respective parameters for the WebServerFIFO
for threads in {2..4}
do
   echo -e "Downloading file with $threads threads and $Cycle Cycles in the WebServer FIFO\n" >> $FILE
   ./bclient $IP $Port $N_File $threads $Cycle >> $FILE 
done

# call the tools of Benchmark with the respective parameters for the WebServerForked
for threads in {2..4}
do
   echo -e "Downloading file with $threads threads and $Cycle Cycles in the WebServer Forked\n" >> $FILE
   ./bclient $IP $Port3 $N_File $threads $Cycle >> $FILE 
done

# call the tools of Benchmark with the respective parameters for the WebServerThreaded
for threads in {2..4}
do
   echo -e "Downloading file with $threads threads and $Cycle Cycles in the WebServer Threaded\n" >> $FILE
   ./bclient $IP $Port5 $N_File $threads $Cycle >> $FILE 
done

# call the tools of Benchmark with the respective parameters for the WebServerPre-fork
for threads in {2..4}
do
   echo -e "Downloading file with $threads threads and $Cycle Cycles in the WebServer Pre-Fork\n" >> $FILE
   ./bclient $IP $Port7 $N_File $threads $Cycle >> $FILE 
done

# call the tools of Benchmark with the respective parameters for the WebServerPre-Threaded
for threads in {2..4}
do
   echo -e "Downloading file with $threads threads and $Cycle Cyclesin the WebServer Pre-Threaded\n" >> $FILE
   ./bclient $IP $Port9 $N_File $threads $Cycle >> $FILE 
done
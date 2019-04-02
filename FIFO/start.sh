#/bin/sh

# Load set up
. ./environment.sh

# Lets compile the software in the host machine using our recipe in the Makefile
echo "--------------------------------------------"
echo "Starting WebServer"
echo "--------------------------------------------"
#/bin/sh

# Load set up
. ./environment.sh

echo "--------------------------------------------"
echo "Starting Container $BIN_NAME"
echo "--------------------------------------------"

sudo docker container start $BIN_NAME
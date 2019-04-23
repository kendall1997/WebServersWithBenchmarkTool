#/bin/sh

# Load set up
. ./environment.sh

echo "--------------------------------------------"
echo "Starting Container $BIN_NAME"
echo "--------------------------------------------"

sudo docker container start $BIN_NAME
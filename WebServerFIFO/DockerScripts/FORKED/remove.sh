#/bin/sh

# Load set up
. ./environment.sh

echo "--------------------------------------------"
echo "Deleting Container $BIN_NAME"
echo "--------------------------------------------"

sudo docker container rm $BIN_NAME
#/bin/sh

# Load set up
. ./environment.sh

echo "--------------------------------------------"
echo "Creating container $BIN_NAME"
echo "--------------------------------------------"

sudo docker run \
	--name $BIN_NAME \
	--publish $HOST_PORT:$CONTAINER_PORT \
	--volume $CONFIG:$CONFIG_OS_PATH \
	--volume $WWW:$PUBLIC_WWW_PATH \
	--volume $LOG:$LOG_PATH \
	--detach \
	$OWNER/$IMAGE:$VERSION 

# Docker Config

BIN_NAME=WebServerFIFO
IMAGE=webserverfifo

# Volumes from Docker Container
CONFIG_OS_PATH=/etc/webserver/
PUBLIC_WWW_PATH=/var/webserver/
LOG_PATH=/var/log/

# Local Path
BASE="`pwd`/volumes$BIN_NAME"

CONFIG=$BASE/config
WWW=$BASE/www
LOG=$BASE/log

# Networking
HOST_PORT=9001
CONTAINER_PORT=8001
# Docker Config

BIN_NAME=WebServerFIFO
IMAGE=webserverfifo
OWNER=kendallgonzalez
VERSION=3.0.0

# Volumes from Docker Container
CONFIG_OS_PATH=/etc/webserver/
PUBLIC_WWW_PATH=/var/webserver/
LOG_PATH=/var/log/

# Volumes cgroup
CGROUP=/sys/fs/cgroup:/sys/fs/cgroup:ro

# Local Path
BASE="`pwd`/../../"
echo $BASE
CONFIG=$BASE/conf
WWW=$BASE/www
LOG=$BASE/log

# Remote path
INSTALL_PATH=/root/webserver

# Networking
HOST_PORT=0.0.0.0:8001
CONTAINER_PORT=8001


# Move to root
cd ../../
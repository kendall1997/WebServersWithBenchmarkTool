#/bin/sh

# Load set up
. ./environment.sh

# Lets compile the software in the host machine using our recipe in the Makefile
echo "--------------------------------------------"
echo "Compiling WebServer"
echo "--------------------------------------------"
make only-bin

# Then, lets build the docker image

# In case the image already exists in the local repository this step is skipped

# We are not using a base image purely due to known bugs running systemd inside a docker container
# This issue is related to Linux Kernel rather than Ubuntu or any other Distribution
# See https://bugzilla.redhat.com/show_bug.cgi?id=1441100, it provides the bug description
# and a way to replicate it.
# 
# We solved this problem using a Ubuntu 16:04 base image, then remove some directories then configure
# systemd

echo "--------------------------------------------"
echo "Creating image $IMAGE:$VERSION"
echo "--------------------------------------------"

sudo docker build --tag=$IMAGE:$VERSION .


# Lets create the container
echo "--------------------------------------------"
echo "Creating container $BIN_NAME"
echo "--------------------------------------------"

# Prepare the host to run privileged containers

# The following command is used to set up the Docker host. 
# It uses special privileges to create a cgroup hierarchy for systemd. 
# We do this in a separate setup step so we can run systemd in unprivileged containers.
# Security First!
# 
# --rm: indicates that the container will be deleted after its execution finish
# --privileged: Give extended privileges to this container from the host's kernel
# --volume: Bind mount a volume from host machine and a docker container instance
sudo docker run --rm --privileged --volume /:/host $IMAGE:$VERSION setup


# Lets run the main container
# 
# --name: Container instance name
# --publish: Networking interaction, enable mapping ports from container and host
# --volume: Bind mount a volume from host machine and a docker container instance
# --security-opt: Security Options
# 	We must disable seccomp because systemd uses system calls that are not allowed by 
# 	Docker's default seccomp profile
# --tmpfs: Mount a tmpfs directory
# 	Ubuntu's systemd expects /run and /run/lock to be tmpfs file systems, but 
# 	it can't mount them itself in an unprivileged container
# --detach: Run container in background and print container ID

sudo docker run \
	--name $BIN_NAME \
	--publish $HOST_PORT:$CONTAINER_PORT \
	--volume $CONFIG:$CONFIG_OS_PATH \
	--volume $WWW:$PUBLIC_WWW_PATH \
	--volume $LOG:$LOG_PATH \
	--volume $CGROUP \
	--security-opt seccomp=unconfined \
	--tmpfs /run \
	--tmpfs /run/lock \
	--detach \
	$IMAGE:$VERSION 


# Lets move the WebServer into the docker container instance
echo "--------------------------------------------"
echo "Copy WebServer and Installing into $BIN_NAME"
echo "--------------------------------------------"

# Copy from host to container
sudo docker cp . $BIN_NAME:$INSTALL_PATH

# Set the config file to the matched scheduler
cp conf/fifo/config.conf conf/config.conf

# Execute make installDocker inside the container
sudo docker exec -it $BIN_NAME make -C $INSTALL_PATH installDocker
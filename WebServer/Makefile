# Costa Rica Institute of Technology
# Computer Engineering
# Operating Systems
# Kendall González León
# 2015087861

# base name
BINARY=WebServer

# each webserver
CONTAINER_INSTANCE_FIFO=WebServerFIFO
CONTAINER_INSTANCE_FORKED=WebServerFORKED
CONTAINER_INSTANCE_THREADED=WebServerTHREADED
CONTAINER_INSTANCE_PREFORKED=WebServerPREFORKED
CONTAINER_INSTANCE_PRETHREADED=WebServerPRETHREADED

# paths
LIB_PATH=lib
SRC_PATH=src
CONF_PATH=conf
BIN_DIR=bin
WWW_DIR=www
LOG_DIR=log

# lib paths
LIB_OS_PATH=/lib/x86_64-linux-gnu/
SYSTEMD_OS_PATH=/etc/systemd/system/
CONFIG_OS_PATH=/etc/webserver/
PUBLIC_WWW_PATH=/var/webserver/
BINARIES_OS_PATH=/usr/bin/

# config file path
CONF_FILE=/var/log/webserver.log

# generate binaries
build:
	$(MAKE) only-bin --no-print-directory

# install the current webserver in the system
install:
	sudo $(MAKE) all --no-print-directory

# uninstall the current webserver in the system
uninstall:
	sudo $(MAKE) all-uninstall --no-print-directory

# install the webserver in a dockerized way
installDocker: install-binary install-daemon
	echo "WebServer Installed for Docker"	

# install all step-by-step
all: structure structure-os binary install-binary install-config install-daemon install-www-content clean
	echo "WebServer Installed"

# uninstall all step-by-step
all-uninstall: undo-structure-os uninstall-binary uninstall-daemon
	echo "WebServer Unistalled"

# only generates binaries
only-bin: structure binary 
	cp $(CONF_PATH)/config.conf $(BIN_DIR)
	echo "Build binaries"

# auxiliar rule, generate binary
binary:
	cd $(SRC_PATH) && $(MAKE)

# auxiliar rule, generate binary
install-www-content:
	cp $(WWW_DIR)/* $(PUBLIC_WWW_PATH)

# auxiliar rule, remove www folder
uninstall-www-content:
	rm $(WWW_DIR) 2>/dev/null 

# auxiliar rule, install config in the system
install-config:
	cp $(CONF_PATH)/config.conf $(CONFIG_OS_PATH)

# auxiliar rule, generate binary
uninstall-config:
	rm $(CONFIG_OS_PATH)config.conf 2>/dev/null 

# auxiliar rule, install binary in the os
install-binary:
	cp $(BIN_DIR)/$(BINARY) $(BINARIES_OS_PATH)
	cp $(CONF_PATH)/webserver-start $(BINARIES_OS_PATH)

# auxiliar rule, uninstall binary in the os
uninstall-binary:
	rm $(BINARIES_OS_PATH)$(BINARY) 2>/dev/null 
	rm $(BINARIES_OS_PATH)webserver-start 2>/dev/null 


# auxiliar rule, install daemon
install-daemon:
	sudo cp $(CONF_PATH)/webserver.service $(SYSTEMD_OS_PATH)
	systemctl enable --now webserver.service
	systemctl start webserver.service

# auxiliar rule, uninstall daemon
uninstall-daemon:
	systemctl stop webserver.service
	systemctl disable webserver.service
	rm -r $(SYSTEMD_OS_PATH)webserver.service 2>/dev/null 
	systemctl daemon-reload
	systemctl reset-failed

# auxiliar rule, install http library
install-library:
	cp $(BIN_DIR)/libhttp.so $(LIB_OS_PATH)

# auxiliar rule, uninstall http library
uninstall-library:
	rm $(LIB_OS_PATH)libhttp.so 2>/dev/null 

# auxiliar rule, create the folder structure
structure:
	mkdir -p $(BIN_DIR)
	mkdir -p $(LOG_DIR)

# auxiliar rule, create the os folder structure
structure-os:
	mkdir -p $(PUBLIC_WWW_PATH)
	mkdir -p $(CONFIG_OS_PATH)

# auxiliar rule, remove the os folder structure
undo-structure-os:
	rm $(PUBLIC_WWW_PATH) -r 2>/dev/null 
	rm $(CONFIG_OS_PATH) -r 2>/dev/null 

# auxiliar rule, start the service
service-start:
	sudo systemctl start webserver.service

# auxiliar rule, gets the status
service-status:
	sudo systemctl status webserver.service

# auxiliar rule, restart service
service-restart:
	sudo systemctl restart webserver.service

# auxiliar rule, stop service
service-stop:
	sudo systemctl stop webserver.service

# auxiliar rule, clean local fs
clean:
	echo "Environment cleaned"
	sudo rm $(BIN_DIR) -rf 2>/dev/null 
	# cd $(LIB_PATH) && $(MAKE) clean --no-print-directory


##
## Docker Utilities
##

# Docker container create
fifo-create:
	@cd DockerScripts/FIFO && ./create.sh

# Docker container start
fifo-start:
	@cd DockerScripts/FIFO && ./start.sh

# Docker container stop
fifo-stop:
	@cd DockerScripts/FIFO && ./stop.sh

# Docker container remove
fifo-remove:
	@cd DockerScripts/FIFO && ./remove.sh

# Docker container attach terminal
fifo-terminal:
	@sudo docker exec -it $(CONTAINER_INSTANCE_FIFO) /bin/bash

# Docker container create
forked-create:
	@cd DockerScripts/FORKED && ./create.sh

# Docker container start
forked-start:
	@cd DockerScripts/FORKED && ./start.sh

# Docker container stop
forked-stop:
	@cd DockerScripts/FORKED && ./stop.sh

# Docker container remove
forked-remove:
	@cd DockerScripts/FORKED && ./remove.sh

# Docker container attach terminal
forked-terminal:
	@sudo docker exec -it $(CONTAINER_INSTANCE_FORKED) /bin/bash

# Docker container create
threaded-create:
	@cd DockerScripts/THREADED && ./create.sh

# Docker container start
threaded-start:
	@cd DockerScripts/THREADED && ./start.sh

# Docker container stop
threaded-stop:
	@cd DockerScripts/THREADED && ./stop.sh

# Docker container remove
threaded-remove:
	@cd DockerScripts/THREADED && ./remove.sh

# Docker container attach terminal
threaded-terminal:
	@sudo docker exec -it $(CONTAINER_INSTANCE_THREADED) /bin/bash

# Docker container create
preforked-create:
	@cd DockerScripts/PREFORKED && ./create.sh

# Docker container start
preforked-start:
	@cd DockerScripts/PREFORKED && ./start.sh

# Docker container stop
preforked-stop:
	@cd DockerScripts/PREFORKED && ./stop.sh

# Docker container remove
preforked-remove:
	@cd DockerScripts/PREFORKED && ./remove.sh

# Docker container attach terminal
preforked-terminal:
	@sudo docker exec -it $(CONTAINER_INSTANCE_PREFORKED) /bin/bash

# Docker container create
prethreaded-create:
	@cd DockerScripts/PRETHREADED && ./create.sh

# Docker container start
prethreaded-start:
	@cd DockerScripts/PRETHREADED && ./start.sh

# Docker container stop
prethreaded-stop:
	@cd DockerScripts/PRETHREADED && ./stop.sh

# Docker container remove
prethreaded-remove:
	@cd DockerScripts/PRETHREADED && ./remove.sh

# Docker container attach terminal
prethreaded-terminal:
	@sudo docker exec -it $(CONTAINER_INSTANCE_PRETHREADED) /bin/bash

# Gets the list of docker container that is running
list:
	@sudo docker container ls


fullDocker:
	@cd DockerScripts && ./installDocker.sh
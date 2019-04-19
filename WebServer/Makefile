# Costa Rica Institute of Technology
# Computer Engineering
# Operating Systems
# Kendall González León
# 2015087861

BINARY=WebServer

CONTAINER_INSTANCE_FIFO=WebServerFIFO
CONTAINER_INSTANCE_FORKED=WebServerFORKED
CONTAINER_INSTANCE_THREADED=WebServerTHREADED
CONTAINER_INSTANCE_PREFORKED=WebServerPREFORKED
CONTAINER_INSTANCE_PRETHREADED=WebServerPRETHREADED

LIB_PATH=lib
SRC_PATH=src
CONF_PATH=conf
BIN_DIR=bin
WWW_DIR=www
LOG_DIR=log


LIB_OS_PATH=/lib/x86_64-linux-gnu/
SYSTEMD_OS_PATH=/etc/systemd/system/
CONFIG_OS_PATH=/etc/webserver/
PUBLIC_WWW_PATH=/var/webserver/
BINARIES_OS_PATH=/usr/bin/

CONF_FILE=/var/log/webserver.log

build:
	$(MAKE) only-bin --no-print-directory

install:
	sudo $(MAKE) all --no-print-directory

uninstall:
	sudo $(MAKE) all-uninstall --no-print-directory

installDocker: install-binary install-daemon
	echo "WebServer Installed for Docker"	

all: structure structure-os binary install-binary install-config install-daemon install-www-content clean
	echo "WebServer Installed"

all-uninstall: undo-structure-os uninstall-binary uninstall-daemon
	echo "WebServer Unistalled"

only-bin: structure binary 
	cp $(CONF_PATH)/config.conf $(BIN_DIR)
	echo "Build binaries"

binary:
	cd $(SRC_PATH) && $(MAKE)

install-www-content:
	cp $(WWW_DIR)/* $(PUBLIC_WWW_PATH)

uninstall-www-content:
	rm $(WWW_DIR) 2>/dev/null 

install-config:
	cp $(CONF_PATH)/config.conf $(CONFIG_OS_PATH)

uninstall-config:
	rm $(CONFIG_OS_PATH)config.conf 2>/dev/null 

install-binary:
	cp $(BIN_DIR)/$(BINARY) $(BINARIES_OS_PATH)
	cp $(CONF_PATH)/webserver-start $(BINARIES_OS_PATH)

uninstall-binary:
	rm $(BINARIES_OS_PATH)$(BINARY) 2>/dev/null 
	rm $(BINARIES_OS_PATH)webserver-start 2>/dev/null 

install-daemon:
	sudo cp $(CONF_PATH)/webserver.service $(SYSTEMD_OS_PATH)
	systemctl enable --now webserver.service
	systemctl start webserver.service

uninstall-daemon:
	systemctl stop webserver.service
	systemctl disable webserver.service
	rm -r $(SYSTEMD_OS_PATH)webserver.service 2>/dev/null 
	systemctl daemon-reload
	systemctl reset-failed

install-library:
	cp $(BIN_DIR)/libhttp.so $(LIB_OS_PATH)

uninstall-library:
	rm $(LIB_OS_PATH)libhttp.so 2>/dev/null 

structure:
	mkdir -p $(BIN_DIR)
	mkdir -p $(LOG_DIR)

structure-os:
	mkdir -p $(PUBLIC_WWW_PATH)
	mkdir -p $(CONFIG_OS_PATH)

undo-structure-os:
	rm $(PUBLIC_WWW_PATH) -r 2>/dev/null 
	rm $(CONFIG_OS_PATH) -r 2>/dev/null 

service-start:
	sudo systemctl start webserver.service

service-status:
	sudo systemctl status webserver.service

service-restart:
	sudo systemctl restart webserver.service

service-stop:
	sudo systemctl stop webserver.service

clean:
	echo "Environment cleaned"
	sudo rm $(BIN_DIR) -rf 2>/dev/null 
	# cd $(LIB_PATH) && $(MAKE) clean --no-print-directory


##
## Docker Utilities
##


fifo-create:
	@cd DockerScripts/FIFO && ./create.sh

fifo-start:
	@cd DockerScripts/FIFO && ./start.sh

fifo-stop:
	@cd DockerScripts/FIFO && ./stop.sh

fifo-remove:
	@cd DockerScripts/FIFO && ./remove.sh

fifo-terminal:
	@sudo docker exec -it $(CONTAINER_INSTANCE_FIFO) /bin/bash

forked-create:
	@cd DockerScripts/FORKED && ./create.sh

forked-start:
	@cd DockerScripts/FORKED && ./start.sh

forked-stop:
	@cd DockerScripts/FORKED && ./stop.sh

forked-remove:
	@cd DockerScripts/FORKED && ./remove.sh

forked-terminal:
	@sudo docker exec -it $(CONTAINER_INSTANCE_FORKED) /bin/bash

threaded-create:
	@cd DockerScripts/THREADED && ./create.sh

threaded-start:
	@cd DockerScripts/THREADED && ./start.sh

threaded-stop:
	@cd DockerScripts/THREADED && ./stop.sh

threaded-remove:
	@cd DockerScripts/THREADED && ./remove.sh

threaded-terminal:
	@sudo docker exec -it $(CONTAINER_INSTANCE_THREADED) /bin/bash

preforked-create:
	@cd DockerScripts/PREFORKED && ./create.sh

preforked-start:
	@cd DockerScripts/PREFORKED && ./start.sh

preforked-stop:
	@cd DockerScripts/PREFORKED && ./stop.sh

preforked-remove:
	@cd DockerScripts/PREFORKED && ./remove.sh

preforked-terminal:
	@sudo docker exec -it $(CONTAINER_INSTANCE_PREFORKED) /bin/bash

prethreaded-create:
	@cd DockerScripts/PRETHREADED && ./create.sh

prethreaded-start:
	@cd DockerScripts/PRETHREADED && ./start.sh

prethreaded-stop:
	@cd DockerScripts/PRETHREADED && ./stop.sh

prethreaded-remove:
	@cd DockerScripts/PRETHREADED && ./remove.sh

prethreaded-terminal:
	@sudo docker exec -it $(CONTAINER_INSTANCE_PRETHREADED) /bin/bash

list:
	@sudo docker container ls




fullDocker:
	@cd DockerScripts && ./installDocker.sh
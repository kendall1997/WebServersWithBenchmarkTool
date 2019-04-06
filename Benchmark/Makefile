# Costa Rica Institute of Technology
# Computer Engineering
# Operating Systems
# Kendall González León
# 2015087861
WD=$(shell pwd)

BIN_NAME=bclient

CC=gcc
CFLAGS=-O2 -lpthread -lcurl

BIN_DIR=bin
HEADER=include


C_FILES=$(wildcard src/*.c)

main: dir build
	@echo "Building binaries"

build:
	@$(CC) -I"$(HEADER)" -o "$(BIN_DIR)/$(BIN_NAME)" $(C_FILES) $(CFLAGS)

curl:
	sudo apt-get install libcurl4-gnutls-dev

dir:
	mkdir -p $(BIN_DIR)

run:
	./$(BIN_DIR)/$(BIN_NAME) autogestion.metrotel.com.ar 80 speedtest/archivo10MB.zip 2 2

clean:
	rm $(BIN_DIR) -rf

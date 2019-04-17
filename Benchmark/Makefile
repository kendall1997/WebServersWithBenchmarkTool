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
BENCH_DIR=benchmarks


C_FILES=$(wildcard src/*.c)

.PHONY: clean main benchmarks

main: dir build benchmarks
	@echo "Building binaries"

benchmarks:
	@echo "Adding benchmark bash files"
	@cp -a $(BENCH_DIR)/. $(BIN_DIR)/

build:
	@$(CC) -I"$(HEADER)" -o "$(BIN_DIR)/$(BIN_NAME)" $(C_FILES) $(CFLAGS)

curl:
	sudo apt-get install libcurl4-gnutls-dev

dir:
	mkdir -p $(BIN_DIR)

clean:
	rm $(BIN_DIR) -rf

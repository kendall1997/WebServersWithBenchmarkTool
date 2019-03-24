# Costa Rica Institute of Technology
# Computer Engineering
# Operating Systems
# Kendall González León
# 2015087861
WD=$(shell pwd)

CC=gcc
CFLAGS= -fpic -Wall -O2 

LIBS=http
LIB_PATH=$(WD)/../lib
HEADER=$(WD)/../include

BIN_DIR=$(WD)/../bin
BIN_NAME=WebServer

C_FILES=$(wildcard *.c)

build: libs dynamic
	@echo "Building binaries"

dynamic:
	@$(CC) -I"$(HEADER)"  -L"$(BIN_DIR)" -Wl,-rpath="$(BIN_DIR)" -o "$(BIN_DIR)/$(BIN_NAME)" $(C_FILES) -l$(LIBS)

libs:
	@cd "$(LIB_PATH)" && $(MAKE) --no-print-directory

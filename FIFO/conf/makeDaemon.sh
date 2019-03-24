#!/bin/bash

cd ..

sudo make

sudo make install 

cd conf

sudo cp webserver.service /etc/systemd/system

cd ..

systemctl enable --now webserver.service
systemctl start webserver.service

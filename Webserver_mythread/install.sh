#/bin/sh

# Install developer tools
# This will install: gcc, g++, make, dpkg-dev, lib6dev
sudo apt-get -y install build-essential

# Lets create a folder for each webserver

# Move one folder up
cd ../
# Make a Copy
cp WebServer WebServerFIFO -r
cp WebServer WebServerFORKED -r
cp WebServer WebServerTHREADED -r
cp WebServer WebServerPREFORKED -r
cp WebServer WebServerPRETHREADED -r

# Install docker & create each webserver

cd WebServerFIFO
make fullDocker
make fifo-create
cd ../

cd WebServerFORKED
make forked-create
cd ../

cd WebServerTHREADED
make threaded-create
cd ../

cd WebServerPREFORKED
make preforked-create
cd ../

cd WebServerPRETHREADED
make prethreaded-create
cd ../

# Finish
echo 'Process Done'
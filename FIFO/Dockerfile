# Use an official ubuntu image as a parent image
FROM ubuntu:18.04

# Set the working directory to /app
WORKDIR /app

# Copy the current directory contents into the container at /app
COPY . /app

# Install any needed packages specified in requirements.txt
RUN apt update && apt install build-essential -y && apt-get install sudo -y && sudo make install-without-daemon

# Make port 8001 available to the world outside this container
EXPOSE 8001

# Run app.py when the container launches
ENTRYPOINT ["/usr/bin/WebServer","/etc/webserver/config.conf"]
# Use an official ubuntu image as a parent image
FROM ubuntu:16.04

ENV container docker

# Don't start any optional services except for the few we need.
RUN find /etc/systemd/system \
    /lib/systemd/system \
    -path '*.wants/*' \
    -not -name '*journald*' \
    -not -name '*systemd-tmpfiles*' \
    -not -name '*systemd-user-sessions*' \
    -exec rm \{} \;

RUN apt-get update && \
    apt-get install -y \
    dbus build-essential sudo curl php libapache2-mod-php && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*

RUN systemctl set-default multi-user.target

RUN mkdir -p /etc/webserver/ && mkdir -p /var/webserver/ && mkdir -p /root/webserver

COPY DockerScripts/setup /sbin/

STOPSIGNAL SIGRTMIN+3

CMD ["/bin/bash", "-c", "exec /sbin/init --log-target=journal 3>&1"]
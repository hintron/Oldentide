# Oldentide Docker File

# How To Use:

# make sure the docker daemon is running (dockerd)
# cd into this directory and run:
#   docker build -t oldentide_server .
#   docker run -it oldentide_server
#   ./bin/Server 1337
# If it isn't going through (on Windows), then you might need to explicitly
# specify the ports in order to force the OS to allow it through the firewall:
#   docker run -it -p 1337:1337/udp oldentide_server


# Base image
# Do 3.5, because sqlite-dev is < 3.19
FROM alpine:3.5

# Set the working directory
WORKDIR /oldentide

# Copy the current directory contents into the container at the working directory
ADD . /oldentide

# --no-cache is like --update, but deletes package list cache automatically
# To search for valid packages, go to https://pkgs.alpinelinux.org/packages
RUN apk --no-cache add \
    bash \
    cmake \
    make\
    g++ \
    git \
    sqlite \
    sqlite-dev

RUN ["make"]

# Make ports available to the world outside this container
# UDP ports need to be explicitly specified
EXPOSE 1337/udp

# Spawn a command line interface
CMD ["bash"]
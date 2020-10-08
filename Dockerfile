FROM	    ubuntu:latest
MAINTAINER  Sam <sam@gigachad.com>

RUN	    apt update -y; apt upgrade -y
RUN	    apt install -y build-essential
RUN	    apt install -y libncurses-dev
ADD	    https://github.com/sambattalio/chad_stride/archive/0.6951.tar.gz /tmp
RUN	    tar xvf /tmp/*.tar.gz -C /tmp
RUN	    cd /tmp/chad_stride-*; make install

ENTRYPOINT  ["/usr/local/bin/chad_stride"]

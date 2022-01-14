# See here for image contents: https://github.com/microsoft/vscode-dev-containers/tree/v0.205.2/containers/cpp/.devcontainer/base.Dockerfile

# [Choice] Debian / Ubuntu version (use Debian 11/9, Ubuntu 18.04/21.04 on local arm64/Apple Silicon): debian-11, debian-10, debian-9, ubuntu-21.04, ubuntu-20.04, ubuntu-18.04
ARG VARIANT="bullseye"
FROM mcr.microsoft.com/vscode/devcontainers/cpp:0-${VARIANT}

# Installing Sipplauncher and it's dependencies
RUN apt-get update && export DEBIAN_FRONTEND=noninteractive \
    && apt-get install -y tcpdump wireshark sngrep

# -------------------
# Install SIPp
RUN apt-get install -y pkg-config dh-autoreconf ncurses-dev build-essential libssl-dev \
    libpcap-dev libncurses5-dev libsctp-dev lksctp-tools cmake \
    && mkdir -p /tmp/sipp \
    && git clone https://github.com/SIPp/sipp.git /tmp/sipp \
    && cd /tmp/sipp \
    && cmake . -DUSE_SSL=1 -DUSE_SCTP=1 -DUSE_PCAP=1 -DUSE_GSL=1 \
    && make all \
    && make install \
    && cd ~/ && rm -rf /tmp/sipp
# -------------------

RUN mkdir -p /tmp/sipplauncher \
    && git clone --recursive https://github.com/zaleos/sipplauncher.git /tmp/sipplauncher \
    && cd /tmp/sipplauncher \
    && git checkout develop \
    && git branch \
    && git rev-parse HEAD \
    && apt-get install -y python3-setuptools \
    # -------------------
    # Python3 hacks
    && sed -i 's/wheel/#wheel/g' requirements.txt \
    && mkdir -p /usr/local/lib/python3.6/site-packages/ \
    # Workaround for scapy's "FileNotFoundError: [Errno 2] No such file or directory: b'liblibc.a'"
    && cd /usr/lib/x86_64-linux-gnu/ \
    && ln -s -f libc.a liblibc.a \
    && cd /tmp/sipplauncher \
    # -------------------
    && make install-all \
    && cd ~/ && rm -rf /tmp/sipplauncher \
    && sipplauncher --help \
    && sipplauncher --version

# [Optional] Uncomment this section to install additional packages.
RUN apt-get update && export DEBIAN_FRONTEND=noninteractive \
    # Build tools 
    && apt-get -y install --no-install-recommends autoconf automake libtool pkg-config

# BerkeleyDB dependency
RUN apt-get -y install libdb++-dev

# Install cajun dependency
RUN cd /var/tmp \
    && git clone https://github.com/cajun-jsonapi/cajun-jsonapi.git \
    && cd cajun-jsonapi \
    && git checkout tags/2.1.1

ENV CPLUS_INCLUDE_PATH /var/tmp/cajun-jsonapi/include
ENV LD_LIBRARY_PATH /usr/local/lib
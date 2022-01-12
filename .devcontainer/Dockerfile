# See here for image contents: https://github.com/microsoft/vscode-dev-containers/tree/v0.205.2/containers/cpp/.devcontainer/base.Dockerfile

# [Choice] Debian / Ubuntu version (use Debian 11/9, Ubuntu 18.04/21.04 on local arm64/Apple Silicon): debian-11, debian-10, debian-9, ubuntu-21.04, ubuntu-20.04, ubuntu-18.04
ARG VARIANT="bullseye"
FROM mcr.microsoft.com/vscode/devcontainers/cpp:0-${VARIANT}

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
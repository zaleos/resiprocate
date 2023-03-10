# FROM debian:bullseye
# FROM debian:squeeze
FROM debian:wheezy

ARG TAG=resiprocate-1.5

# Adjusting repos for old Debian version
# RUN echo "deb [trusted=yes] http://archive.debian.org/debian/ squeeze contrib main non-free" > /etc/apt/sources.list \
#  && echo "deb [trusted=yes] http://archive.debian.org/debian-security squeeze/updates main" >> /etc/apt/sources.list \
#  && apt-get install debian-archive-keyring
RUN echo "deb [trusted=yes] http://archive.debian.org/debian/ wheezy contrib main non-free" > /etc/apt/sources.list \
 && echo "deb [trusted=yes] http://archive.debian.org/debian-security wheezy/updates main" >> /etc/apt/sources.list \
 && apt-get install debian-archive-keyring

RUN apt-get --allow-unauthenticated update \
 && apt-get --allow-unauthenticated install -y \
    ca-certificates \
    wget \
    build-essential \
    autoconf \
    automake \
    libssl-dev \
    libdb++-dev \
    libpopt-dev

# RUN wget https://github.com/resiprocate/resiprocate/archive/refs/tags/${TAG}.tar.gz \
#  && tar zxvf ${TAG}.tar.gz \
#  && rm ${TAG}.tar.gz \
#  && mv resiprocate-${TAG} ${TAG}

RUN mkdir ${TAG}
COPY ./ /${TAG}/
RUN ls -la /${TAG}

# Building older versions
RUN cd ${TAG} \
 && ./configure --disable-ssl --enable-repro --enable-popt \
 && make -j 16 \
 && mkdir /repro && make DESTDIR=/repro install install-repro


# Building latest versions of resiprocate
# RUN cd ${TAG} \
#  && autoreconf --install \
#  && ./configure --with-repro --with-popt \
#  && make -j 8 \
#  && mkdir /repro && make DESTDIR=/repro install

CMD /repro/usr/local/sbin/repro

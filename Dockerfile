FROM ubuntu:18.04

RUN apt-get update -qq && apt-get install -y \
      automake \
      build-essential \
      git \
      liblz4-dev \
      liblzo2-dev \
      libpam0g-dev \
      libssl-dev \
      libtool \
      pkg-config \
      wget

WORKDIR /usr/src/openvpn-auth-aad
COPY . /usr/src/openvpn-auth-aad

RUN ./bootstrap.sh && \
    make

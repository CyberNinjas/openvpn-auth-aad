FROM cyberninjas/pam_aad:ubuntu

RUN apt-get update -qq && apt-get install -y \
      liblz4-dev \
      liblzo2-dev \
      wget

WORKDIR /usr/src/openvpn-auth-aad
COPY . /usr/src/openvpn-auth-aad

RUN ./bootstrap.sh && \
    make

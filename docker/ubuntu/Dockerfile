FROM cyberninjas/pam_aad:ubuntu

RUN apt-get update -qq && apt-get install -y \
      liblz4-dev \
      liblzo2-dev \
      wget

WORKDIR /usr/src/openvpn-auth-aad
COPY . /usr/src/openvpn-auth-aad
RUN useradd -m dev -s /bin/bash && \
    chown -R dev:dev /usr/src/openvpn-auth-aad

USER dev
RUN ./bootstrap.sh && \
    make

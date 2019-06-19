FROM cyberninjas/pam_aad:debian
ARG VERSION
ARG DEBVER

RUN apt-get update -qq && apt-get install -y \
      liblz4-dev \
      liblzo2-dev \
      openvpn \
      wget

WORKDIR /usr/src/openvpn-auth-aad
COPY . /usr/src/openvpn-auth-aad
RUN useradd -m dev -s /bin/bash && \
    chown -R dev:dev /usr/src/openvpn-auth-aad

RUN ./bootstrap.sh && \
    tar cvzf "../openvpn-auth-aad_${VERSION}.orig.tar.gz" --exclude='.git*' . && \
    debuild -us -uc -d -i'(.*)' && \
    dpkg -i "../openvpn-auth-aad_${VERSION}-${DEBVER}_amd64.deb"


#!/bin/sh

git submodule update --init --recursive

# Required for openvpn-plugin.h
cd openvpn && \
   autoreconf -fiv && \
   ./configure && cd .. || exit 1

cd pam_aad && \
   ./bootstrap.sh && \
   ./configure && cd .. || exit 1


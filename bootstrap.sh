#!/bin/sh

git submodule update --init --recursive

# Required for openvpn-plugin.h
cd openvpn && \
   autoreconf -fiv && \
   ./configure


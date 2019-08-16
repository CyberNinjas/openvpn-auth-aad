#!/bin/sh
set -eu

# Recursively build docker images
recursive_build() {
  path=$1
  tag=$2
  release=$3
  for dir in $path/docker/*; do
    if [ -d "${dir}" ]; then
      distro=$(basename "${dir}")
      image="${tag}:${distro}" # org/image:tag
      docker build --build-arg VERSION="${release}" \
                   --build-arg DEBVER=1 \
                   -t "${image}" "${path}" \
                   -f "${dir}/Dockerfile"
    fi
  done
}

main() {
  DEFAULT_IMAGE="cyberninjas/openvpn-auth-aad"
  RELEASE=$(git describe --tags "$(git rev-list --tags --max-count=1)")
  export RELEASE

  # Build all docker images
  recursive_build . "${DEFAULT_IMAGE}" "${RELEASE}"

  sed "s/{{version}}/${RELEASE}/" .bintray.json.in > bintray.json
}

main

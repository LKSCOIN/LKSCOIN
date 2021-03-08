#!/usr/bin/env bash

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd $DIR/..

DOCKER_IMAGE=${DOCKER_IMAGE:-lkspay/lksd-develop}
DOCKER_TAG=${DOCKER_TAG:-latest}

BUILD_DIR=${BUILD_DIR:-.}

rm docker/bin/*
mkdir docker/bin
cp $BUILD_DIR/src/lksd docker/bin/
cp $BUILD_DIR/src/lks-cli docker/bin/
cp $BUILD_DIR/src/lks-tx docker/bin/
strip docker/bin/lksd
strip docker/bin/lks-cli
strip docker/bin/lks-tx

docker build --pull -t $DOCKER_IMAGE:$DOCKER_TAG -f docker/Dockerfile docker

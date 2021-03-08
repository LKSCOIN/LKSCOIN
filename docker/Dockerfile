FROM debian:stretch
LABEL maintainer="LksCoin Developers <admin@lksfoundation.org>"
LABEL description="Dockerised LksCore, built from Travis"

RUN apt-get update && apt-get -y upgrade && apt-get clean && rm -fr /var/cache/apt/*

COPY bin/* /usr/bin/

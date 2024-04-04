FROM ubuntu:22.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y cmake build-essential curl libcurl4-openssl-dev openssl libssl-dev git zlib1g zlib1g-dev
WORKDIR /tcpunch-eval
COPY . .
RUN ./setup.sh

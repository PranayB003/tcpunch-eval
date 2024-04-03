FROM ubuntu:22.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y cmake build-essential curl libcurl4-openssl-dev openssl libssl-dev git zlib1g zlib1g-dev
RUN git clone https://github.com/PranayB003/tcpunch-eval.git
RUN cd tcpunch-eval && ./setup.sh

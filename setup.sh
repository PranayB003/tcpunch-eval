# Build tcpunch client library and server binary
mkdir -p extern/tcpunch/client/build
mkdir -p extern/tcpunch/server/build
cd extern/tcpunch/client/build/
cmake .. && make
cd -
cd extern/tcpunch/server/build/
cmake .. && make
cd -

# Build test clients for evaluating tcpunch
mkdir build
cd build && cmake .. && make && cd -
mkdir bin && cp build/node-* extern/tcpunch/server/build/tcpunchd bin/

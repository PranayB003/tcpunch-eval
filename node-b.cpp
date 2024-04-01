#include <iostream>
#include "./extern/tcpunch/client/tcpunch.h"

int main(int argc, char**argv) {
  // Doesn't handle all errors, assumes second arg is valid IP Addr if given
  if (argc != 2) {
    printf("Usage: ./%s <hole_punching_server_ip>\n", argv[0]);
    return 1;
  }

  int sock_fd = pair("test_group", argv[1]);

  char buf[100] = {};
  int n = recv(sock_fd, buf, sizeof(buf) - 1, 0);
  if (n < 0) {
    std::cout << "recv() error" << std::endl;
    return 1;
  }
  std::cout << "Node A says: " << std::string(buf) << std::endl;
  return 0;
}

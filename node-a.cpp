#include <iostream>
#include <cstring>
#include "./extern/tcpunch/client/tcpunch.h"

int main(int argc, char **argv) {
  // Doesn't handle all errors, assumes second arg is valid IP Addr if given
  if (argc != 2) {
    printf("Usage: ./%s <hole_punching_server_ip>\n", argv[0]);
    return 1;
  }

  int sock_fd = pair("test_group", argv[1]);

  char buf[100] = {};
  std::cout << "Enter message for Node B: " << std::endl;
  std::cin.getline(buf, sizeof(buf) - 1);
  int bytes = send(sock_fd, buf, strlen(buf), 0);

  return 0;
}

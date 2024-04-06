#include <google/cloud/functions/framework.h>
#include <cstdlib>
#include "./deps/tcpunch.h"

namespace gcf = ::google::cloud::functions;

auto contact_vm() {
  return gcf::MakeFunction([](gcf::HttpRequest const& request) {
    char msg[] = "Hello from Cloud Run instance!";
    auto const* ip_addr = std::getenv("HPS_IP");

    std::cout << "Attempting to pair" << std::endl;
    int sock_fd = pair("test_group", ip_addr);
    int bytes = send(sock_fd, msg, strlen(msg), 0);
    if (bytes <= 0) {
      std::cout << "FAILED sending message to VM" << std::endl;
    }

    std::string success = "Message sent to VM";
    return gcf::HttpResponse{}
        .set_header("Content-Type", "text/plain")
        .set_payload(success);
  });
}

int main(int argc, char* argv[]) {
  return gcf::Run(argc, argv, contact_vm());
}

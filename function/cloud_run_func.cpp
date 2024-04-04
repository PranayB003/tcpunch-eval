#include <google/cloud/functions/framework.h>
#include <cstdlib>
#include "./../extern/tcpunch/client/tcpunch.h"

namespace gcf = ::google::cloud::functions;

auto contact_vm() {
  return gcf::MakeFunction([](gcf::HttpRequest const& /*request*/) {
    char *msg = "Hello from cloud run instance!"
    auto const* ip_addr = std::getenv("HPS_IP");

    int sock_fd = pair("test_group", ip_addr);
    int bytes = send(sock_fd, buf, strlen(buf), 0);
    close(sock_fd);

    std::string success = "Message sent to VM";

    return gcf::HttpResponse{}
        .set_header("Content-Type", "text/plain")
        .set_payload(success);
  });
}

int main(int argc, char* argv[]) {
  return gcf::Run(argc, argv, contact_vm());
}

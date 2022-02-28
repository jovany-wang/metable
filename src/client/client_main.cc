#include "common/logging.h"
#include <fstream>
#include <iostream>

#include "src/client/metable_client.h"
#include "src/common/constants.h"
#include "src/protobuf/rpc.grpc.pb.h"

int main(int argc, char **argv) {
  // Instantiate the client. It requires a channel, out of which the actual RPCs
  // are created. This channel models a connection to an endpoint specified by
  // the argument "--target=" which is the only expected argument.
  // We indicate that the channel isn't authenticated (use of
  // InsecureChannelCredentials()).
  std::string target_str;
  std::string arg_str("--target");
  if (argc > 1) {
    std::string arg_val = argv[1];
    size_t start_pos = arg_val.find(arg_str);
    if (start_pos != std::string::npos) {
      start_pos += arg_str.size();
      if (arg_val[start_pos] == '=') {
        target_str = arg_val.substr(start_pos + 1);
      } else {
        std::cout << "The only correct argument syntax is --target="
                  << std::endl;
        return 0;
      }
    } else {
      std::cout << "The only acceptable argument is --target=" << std::endl;
      return 0;
    }
  } else {
    target_str = "localhost:10001";
  }

  metable::MetableClient metable_client(
      grpc::CreateChannel(target_str, grpc::InsecureChannelCredentials()));
  std::string user("qingwang");
  bool result = metable_client.CheckVersion(user);
  std::cout << "Version matched ==" << result << std::endl;

  return 0;
}

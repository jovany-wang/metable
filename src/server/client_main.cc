#include "common/logging.h"
#include <fstream>
#include <iostream>

#include "src/protobuf/rpc.grpc.pb.h"
#include "src/common/constants.h"

#include "grpcpp/grpcpp.h"
#include "grpcpp/health_check_service_interface.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;

#include "src/protobuf/rpc.grpc.pb.h"
#include <grpcpp/grpcpp.h>

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;

namespace metable {

class MetableClient {
public:
  MetableClient(std::shared_ptr<Channel> channel)
      : stub_(metable::rpc::Metable::NewStub(channel)) {}

  // Assembles the client's payload, sends it and presents the response back
  // from the server.
  bool CheckVersion(const std::string &user) {
    // Data we are sending to the server.
    rpc::CheckVersionRequest request;
    request.set_version_str(VERSION_STR);

    // Container for the data we expect from the server.
    rpc::CheckVersionReply reply;

    // Context for the client. It could be used to convey extra information to
    // the server and/or tweak certain RPC behaviors.
    ClientContext context;

    // The actual RPC.
    Status status = stub_->CheckVersion(&context, request, &reply);

    // Act upon its status.
    if (status.ok()) {
      return reply.status() == rpc::CheckVersionStatus::OK;
    } else {
      std::cout << "Failed to RPC. status = " << status.error_message() << std::endl;
      return false;
    }
  }

private:
  std::unique_ptr<metable::rpc::Metable::Stub> stub_;
};

} // namespace metable


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

  metable::MetableClient greeter(
      grpc::CreateChannel(target_str, grpc::InsecureChannelCredentials()));
  std::string user("qingwang");
  bool result = greeter.CheckVersion(user);
  std::cout << "Version matched ==" << result << std::endl;

  return 0;
}

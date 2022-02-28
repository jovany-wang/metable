#include "metable_client.h"

namespace metable {

bool MetableClient::CheckVersion(const std::string &user) {
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
    std::cout << "Failed to RPC. status = " << status.error_message()
              << std::endl;
    return false;
  }
}

} // namespace metable

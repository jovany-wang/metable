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

namespace metable {

class MetableServiceImpl : public rpc::Metable::Service {

public:
  virtual grpc::Status CheckVersion(::grpc::ServerContext *context,
                                const rpc::CheckVersionRequest *request,
                                rpc::CheckVersionReply *reply) override {
    std::cout << "Received version str = " << request->version_str();
    if (VERSION_STR == request->version_str()) {
      reply->set_status(rpc::CheckVersionStatus::OK);
    } else {
      reply->set_status(rpc::CheckVersionStatus::DISMATCHED);
    }
    return grpc::Status::OK;
  }
};

} // namespace metable

int main(int argc, char **argv) {
  metable::MetableLog::StartMetableLog(
      "log/test.log", metable::MetableLogLevel::RLL_INFO, 10, 3);
  std::cout << "Metable Loading." << std::endl;
  metable::MetableLog::ShutDownMetableLog();
  std::fstream file("log/test.log");

  {
    /// For grpc server
    std::string server_address("0.0.0.0:10001");
    metable::MetableServiceImpl service;

    grpc::EnableDefaultHealthCheckService(true);
    // grpc::reflection::InitProtoReflectionServerBuilderPlugin();

    ServerBuilder builder;
    // Listen on the given address without any authentication mechanism.
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    // Register "service" as the instance through which we'll communicate with
    // clients. In this case it corresponds to an *synchronous* service.
    builder.RegisterService(&service);
    // Finally assemble the server.
    std::unique_ptr<Server> server(builder.BuildAndStart());
    std::cout << "Server listening on " << server_address << std::endl;

    // Wait for the server to shutdown. Note that some other thread must be
    // responsible for shutting down the server for this call to ever return.
    server->Wait();
  }

  return 0;
}

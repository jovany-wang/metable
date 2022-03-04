#pragma once

#include "common/logging.h"
#include "src/common/constants.h"
#include "src/protobuf/rpc.grpc.pb.h"
#include <fstream>
#include <iostream>
#include <memory>
#include <vector>

#include "grpcpp/grpcpp.h"
#include "grpcpp/health_check_service_interface.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;

namespace metable {

/// RPC service of Metable.
class MetableServiceImpl : public rpc::Metable::Service {

public:
  virtual grpc::Status CheckVersion(::grpc::ServerContext *context,
                                    const rpc::CheckVersionRequest *request,
                                    rpc::CheckVersionReply *reply) override;

  virtual grpc::Status CreateTable(::grpc::ServerContext *context,
                                   const rpc::CreateTableRequest *request,
                                   rpc::CreateTableReply *reply) override;

private:
  // All tables in memeory！
  std::unordered_map<std::string, std::vector<rpc::Field>> all_tables;
};

/// The server of Metable.
class MetableServer final {

public:
  void Loop();

  /// Gracefully stop this metable server.
  void Stop();

private:
  std::unique_ptr<Server> grpc_server_ = nullptr;
};

} // namespace metable

#pragma once

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

/// RPC service of Metable.
class MetableServiceImpl : public rpc::Metable::Service {

public:
  virtual grpc::Status CheckVersion(::grpc::ServerContext *context,
                                const rpc::CheckVersionRequest *request,
                                rpc::CheckVersionReply *reply) override;

    virtual grpc::Status CreateTable(::grpc::ServerContext *context,
                                const rpc::CreateTableRequest *request,
                                rpc::CreateTableReply *reply) override;
};

/// The server of Metable.
class MetableServer final {

public:
    void Loop();

private:

};

} // namespace metable

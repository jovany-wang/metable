#pragma once

#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <shared_mutex>

#include "common/logging.h"
#include "grpcpp/grpcpp.h"
#include "grpcpp/health_check_service_interface.h"
#include "src/common/constants.h"
#include "src/protobuf/rpc.grpc.pb.h"

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

    virtual grpc::Status CreateDataBase(::grpc::ServerContext *context,
                                        const rpc::CreateDataBaseRequest *request,
                                        rpc::CreateDataBaseReply *reply) override;

    virtual grpc::Status CreateTable(::grpc::ServerContext *context,
                                     const rpc::CreateTableRequest *request,
                                     rpc::CreateTableReply *reply) override;

    virtual grpc::Status TableExist(::grpc::ServerContext *context,
                                    const rpc::TableExistRequest *request,
                                    rpc::TableExistReply *reply) override;

    virtual grpc::Status DropTable(::grpc::ServerContext *context,
                                   const rpc::DropTableRequest *request,
                                   rpc::DropTableReply *reply) override;

private:
    // All DataBase name in memeory！
    mutable std::shared_timed_mutex mutex_;
    std::map<std::string, std::map<std::string, std::vector<rpc::Field> > > all_dbs_;
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

}  // namespace metable

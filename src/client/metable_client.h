#pragma once

#include <fstream>
#include <iostream>

#include "common/logging.h"
#include "grpcpp/grpcpp.h"
#include "grpcpp/health_check_service_interface.h"
#include "src/common/constants.h"
#include "src/protobuf/rpc.grpc.pb.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;

#include <grpcpp/grpcpp.h>

#include "src/protobuf/rpc.grpc.pb.h"

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
    bool CheckVersion(const std::string &user);

    // Create a table on the Metable server!
    // Use the table name and field list to create the meta information of a
    // table. Returns a pair type result. First represents the operation status
    // and second represents the description of the result. Warning !!! The field
    // name in the vector should not be repeated. You should carefully check it
    // before calling this method.
    std::pair<bool, std::string> CreateTable(
        const std::string &name,
        const std::vector<std::pair<std::string, rpc::FieldType>> &fields);

    std::pair<bool, std::string> IsExistTable(const std::string &name);

    std::pair<bool, std::string> DeleteTable(const std::string &name);

private:
    std::unique_ptr<metable::rpc::Metable::Stub> stub_;
};

}  // namespace metable

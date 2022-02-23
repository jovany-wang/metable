#pragma once

#include "common/logging.h"
#include <fstream>
#include <iostream>
#include <map>
#include <vector>

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
  bool CheckVersion(const std::string &user);

  // creta table info
  // first param : what's name for the table you want
  // second param : the fields of table
  bool CreateTable(const std::string &table_name, const std::vector<std::pair<std::string, std::string>> &field);

private:
  std::unique_ptr<metable::rpc::Metable::Stub> stub_;
};

} // namespace metable

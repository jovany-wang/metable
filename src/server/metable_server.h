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

private:

    // Stores descriptions of all tables
    std::map<std::string, 
            std::vector<std::pair<std::string, std::string>>> table_info;

public:
    void Loop();

    /*
        append table schema to global table schema
    */
    void add_table_info(const std::string &name, 
                        const std::vector<std::pair<std::string, std::string>> &vec) {
        table_info.insert(std::make_pair(name, vec));
    }

    /*
        return table info
    */
    std::map<std::string, 
            std::vector<std::pair<std::string, std::string>>> getTableInfo() {
        return table_info;
    }

    /*
        print table info。
    */
    void printTableInfo(){
        for (auto &item : table_info) {
            std::cout << item.first << std::endl;
            for (auto &_item : item.second) {
                std::cout << _item.first << ", " << _item.second << std::endl;
            }
        }
    };

};

} // namespace metable

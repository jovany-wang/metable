#include "metable_server.h"

namespace metable {

grpc::Status MetableServiceImpl::CheckVersion(::grpc::ServerContext *context,
                                              const rpc::CheckVersionRequest *request,
                                              rpc::CheckVersionReply *reply) {
    std::cout << "Received version str = " << request->version_str();
    if (VERSION_STR == request->version_str()) {
        reply->set_status(rpc::CheckVersionStatus::OK);
    } else {
        reply->set_status(rpc::CheckVersionStatus::DISMATCHED);
    }
    return grpc::Status::OK;
}

grpc::Status MetableServiceImpl::CreateDataBase(::grpc::ServerContext *context,
                                                const rpc::CreateDataBaseRequest *request,
                                                rpc::CreateDataBaseReply *reply) {
    std::unique_lock<std::shared_timed_mutex> lock(mutex_);
    const std::string &db_name = request->db_name();

    if (all_dbs.find(db_name) != all_dbs.end()) {
        reply->set_msg("DataBase  exists...");
        reply->set_status(rpc::CreateDataBaseStatus::CREATE_DATA_BASE_FAIL);
        return grpc::Status::OK;
    }
    std::map<std::string, std::vector<rpc::Field>> db;
    auto result = all_dbs.insert(std::make_pair(db_name, db));
    if (result.second) {  // Insert success.
        reply->set_msg("Create DataBase success...");
        reply->set_status(rpc::CreateDataBaseStatus::CREATE_DATA_BASE_SUCCESS);
    } else {  // Insert fail.
        reply->set_msg("DataBase already exists...");
        reply->set_status(rpc::CreateDataBaseStatus::CREATE_DATA_BASE_FAIL);
    }
    return grpc::Status::OK;
}

grpc::Status MetableServiceImpl::CreateTable(::grpc::ServerContext *context,
                                             const rpc::CreateTableRequest *request,
                                             rpc::CreateTableReply *reply) {
    std::unique_lock<std::shared_timed_mutex> lock(mutex_);
    const std::string &db_name = request->db_name();
    const std::string &table_name = request->table_name();
    std::vector<rpc::Field> fields;
    long size = request->fields_size();
    for (long i = 0; i < size; i++) {
        fields.emplace_back(request->fields(i));
    }
    if (all_dbs.find(db_name) == all_dbs.end()) {
        reply->set_msg("DataBase not exists...");
        reply->set_status(rpc::CreateTableStatus::CREATE_TABLE_FAIL);
        return grpc::Status::OK;
    }
    auto &db = all_dbs.find(db_name)->second;
    auto result = db.insert(std::make_pair(table_name, fields));
    if (result.second) {  // Insert success.
        reply->set_msg("Create table success...");
        reply->set_status(rpc::CreateTableStatus::CREATE_TABLE_SUCCESS);
    } else {  // Insert fail.
        reply->set_msg("Table already exists...");
        reply->set_status(rpc::CreateTableStatus::CREATE_TABLE_FAIL);
    }
    return grpc::Status::OK;
}

grpc::Status MetableServiceImpl::TableExist(::grpc::ServerContext *context,
                                            const rpc::TableExistRequest *request,
                                            rpc::TableExistReply *reply) {
    std::shared_lock<std::shared_timed_mutex> lock(mutex_);
    const std::string &db_name = request->db_name();
    const std::string &table_name = request->table_name();

    if (all_dbs.find(db_name) == all_dbs.end()) {
        reply->set_msg("DataBase not exists...");
        reply->set_status(rpc::TableExistStatus::TABLE_NOT_EXIST);
        return grpc::Status::OK;
    }
    auto db = all_dbs.find(db_name)->second;
    if (db.find(table_name) != db.end()) {
        // table_name exist
        reply->set_msg("This table is exists.");
        reply->set_status(rpc::TableExistStatus::TABLE_EXIST);
    } else {
        // table_name is not exist.
        reply->set_msg("This table is not exists.");
        reply->set_status(rpc::TableExistStatus::TABLE_NOT_EXIST);
    }
    return grpc::Status::OK;
}

grpc::Status MetableServiceImpl::DropTable(::grpc::ServerContext *context,
                                           const rpc::DropTableRequest *request,
                                           rpc::DropTableReply *reply) {
    std::unique_lock<std::shared_timed_mutex> lock(mutex_);
    const std::string &db_name = request->db_name();
    const std::string &table_name = request->table_name();
    if (all_dbs.find(db_name) == all_dbs.end()) {
        reply->set_msg("DataBase not exists...");
        reply->set_status(rpc::DropTableStatus::DROP_TABLE_FAIL);
        return grpc::Status::OK;
    }
    auto db = all_dbs.find(db_name)->second;

    auto it = db.find(table_name);
    if (it == db.end()) {
        // table_name is not exist, should not need to be deleted.
        reply->set_msg("This table is not exists, do nothing.");
        reply->set_status(rpc::DropTableStatus::DROP_TABLE_FAIL);
    } else {
        // table_name exist, should be deleted.
        db.erase(it);
        reply->set_msg("This table delete success");
        reply->set_status(rpc::DropTableStatus::DROP_TABLE_SUCCESS);
    }
    return grpc::Status::OK;
}

void MetableServer::Loop() {
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
    grpc_server_ = std::move(builder.BuildAndStart());
    std::cout << "Server listening on " << server_address << std::endl;

    // Wait for the server to shutdown. Note that some other thread must be
    // responsible for shutting down the server for this call to ever return.
    grpc_server_->Wait();
}

void MetableServer::Stop() { grpc_server_->Shutdown(); }

}  // namespace metable

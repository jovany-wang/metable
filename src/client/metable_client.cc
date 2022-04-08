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
        std::cout << "Failed to RPC. status = " << status.error_message() << std::endl;
        return false;
    }
}

std::pair<bool, std::string> MetableClient::CreateDataBase(const std::string &db_name) {
    rpc::CreateDataBaseRequest request;
    request.set_db_name(db_name);

    rpc::CreateDataBaseReply reply;
    ClientContext context;
    Status status = stub_->CreateDataBase(&context, request, &reply);
    if (status.ok()) {
        return std::make_pair(
            reply.status() == rpc::CreateDataBaseStatus::CREATE_DATA_BASE_SUCCESS,
            reply.msg());
    }
    return std::make_pair(false, "An error occurred on the server.");
}

std::pair<bool, std::string> MetableClient::CreateTable(
    const std::string &db_name, const std::string &table_name,
    const std::vector<std::pair<std::string, rpc::FieldType>> &fields) {
    rpc::CreateTableRequest request;
    request.set_db_name(db_name);
    request.set_table_name(table_name);
    // Add field to fields.
    rpc::Field *field;
    for (const auto &field_item : fields) {
        field = request.add_fields();
        field->set_name(field_item.first);
        field->set_type(field_item.second);
    }
    rpc::CreateTableReply reply;
    ClientContext context;
    Status status = stub_->CreateTable(&context, request, &reply);
    if (status.ok()) {
        return std::make_pair(
            reply.status() == rpc::CreateTableStatus::CREATE_TABLE_SUCCESS, reply.msg());
    }
    return std::make_pair(false, "An error occurred on the server.");
}

std::pair<bool, std::string> MetableClient::TableExist(const std::string &db_name,
                                                       const std::string &table_name) {
    rpc::TableExistRequest request;
    request.set_db_name(db_name);
    request.set_table_name(table_name);
    rpc::TableExistReply reply;
    ClientContext context;
    Status status = stub_->TableExist(&context, request, &reply);
    if (status.ok()) {
        return std::make_pair(reply.status() == rpc::TableExistStatus::TABLE_EXIST,
                              reply.msg());
    }
    return std::make_pair(false, "An error occurred on the server.");
}

std::pair<bool, std::string> MetableClient::DropTable(const std::string &db_name,
                                                      const std::string &table_name) {
    rpc::DropTableRequest request;
    request.set_db_name(db_name);
    request.set_table_name(table_name);
    rpc::DropTableReply reply;
    ClientContext context;
    Status status = stub_->DropTable(&context, request, &reply);
    if (status.ok()) {
        return std::make_pair(reply.status() == rpc::DropTableStatus::DROP_TABLE_SUCCESS,
                              reply.msg());
    }
    return std::make_pair(false, "An error occurred on the server.");
}

}  // namespace metable

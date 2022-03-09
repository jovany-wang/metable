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

std::pair<bool, std::string> MetableClient::CreateTable(
    const std::string &name,
    const std::vector<std::pair<std::string, rpc::FieldType>> &fields) {
    rpc::CreateTableRequest request;
    request.set_table_name(name);
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
        return std::make_pair(reply.status() == rpc::CreateTableStatus::SUCCESS,
                              reply.msg());
    }
    return std::make_pair(false, "An error occurred on the server.");
}

std::pair<bool, std::string> MetableClient::TableExist(const std::string &name) {
    rpc::TableExistRequest request;
    request.set_table_name(name);
    rpc::TableExistReply reply;
    ClientContext context;
    Status status = stub_->TableExist(&context, request, &reply);
    if (status.ok()) {
        return std::make_pair(reply.status() == rpc::TableExistStatus::TABLE_EXIST,
                              reply.msg());
    }
    return std::make_pair(false, "An error occurred on the server.");
}

std::pair<bool, std::string> MetableClient::DropTable(const std::string &name) {
    rpc::DropTableRequest request;
    request.set_table_name(name);
    rpc::DropTableReply reply;
    ClientContext context;
    Status status = stub_->DropTable(&context, request, &reply);
    if (status.ok()) {
        return std::make_pair(
            reply.status() == rpc::DropTableStatus::DROP_TABLE_SUCCESS, reply.msg());
    }
    return std::make_pair(false, "An error occurred on the server.");
}

}  // namespace metable

#include "client/metable_client.h"
#include "gtest/gtest.h"
#include "server/metable_server.h"

TEST(RpcTest, TestCheckVersion) {
    metable::MetableServer metable_server;
    std::thread server_thread([&metable_server]() { metable_server.Loop(); });

    metable::MetableClient metable_client(
        grpc::CreateChannel("localhost:10001", grpc::InsecureChannelCredentials()));
    std::string user("qingwang");
    bool result = metable_client.CheckVersion(user);
    ASSERT_TRUE(result);
    metable_server.Stop();
    server_thread.join();
}

TEST(RpcTest, TestCreateTable) {
    metable::MetableServer metable_server;
    std::thread server_thread([&metable_server]() { metable_server.Loop(); });

    metable::MetableClient metable_client(
        grpc::CreateChannel("localhost:10001", grpc::InsecureChannelCredentials()));

    std::string db_name = "test_db";
    auto result = metable_client.CreateDataBase(db_name);
    std::string table_name = "test_table";
    std::vector<std::pair<std::string, metable::rpc::FieldType>> fields;
    fields.push_back(std::make_pair("name", metable::rpc::FieldType::STRING));
    fields.push_back(std::make_pair("age", metable::rpc::FieldType::INT));
    auto create_table_result = metable_client.CreateTable(db_name, table_name, fields);
    ASSERT_TRUE(create_table_result.first);
    metable_server.Stop();
    server_thread.join();
}

TEST(RpcTest, TestTableExist) {
    metable::MetableServer metable_server;
    std::thread server_thread([&metable_server]() { metable_server.Loop(); });

    metable::MetableClient metable_client(
        grpc::CreateChannel("localhost:10001", grpc::InsecureChannelCredentials()));

    std::string db_name = "test_db1";
    metable_client.CreateDataBase(db_name);
    std::string table_name = "test_table111";
    std::vector<std::pair<std::string, metable::rpc::FieldType>> fields;
    fields.push_back(std::make_pair("name", metable::rpc::FieldType::STRING));
    fields.push_back(std::make_pair("age", metable::rpc::FieldType::INT));
    metable_client.CreateTable(db_name, table_name, fields);
    auto TableExistResult = metable_client.TableExist(db_name, table_name);
    ASSERT_TRUE(TableExistResult.first);
    metable_server.Stop();
    server_thread.join();
}

TEST(RpcTest, TestDropTable) {
    metable::MetableServer metable_server;
    std::thread server_thread([&metable_server]() { metable_server.Loop(); });

    metable::MetableClient metable_client(
        grpc::CreateChannel("localhost:10001", grpc::InsecureChannelCredentials()));

    std::string db_name = "test_db";
    metable_client.CreateDataBase(db_name);
    std::string table_name = "test_table";
    std::vector<std::pair<std::string, metable::rpc::FieldType>> fields;
    fields.push_back(std::make_pair("name", metable::rpc::FieldType::STRING));
    fields.push_back(std::make_pair("age", metable::rpc::FieldType::INT));
    metable_client.CreateTable(db_name, table_name, fields);
    auto DropTableResult = metable_client.DropTable(db_name, table_name);
    ASSERT_TRUE(DropTableResult.first);

    metable_server.Stop();
    server_thread.join();
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

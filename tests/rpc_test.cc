#include "client/metable_client.h"
#include "server/metable_server.h"

#include "gtest/gtest.h"

TEST(RpcTest, TestCheckVersion) {
  metable::MetableServer metable_server;
  std::thread server_thread([&metable_server]() { metable_server.Loop(); });

  metable::MetableClient metable_client(grpc::CreateChannel(
      "localhost:10001", grpc::InsecureChannelCredentials()));
  std::string user("qingwang");
  bool result = metable_client.CheckVersion(user);
  ASSERT_TRUE(result);
  metable_server.Stop();
  server_thread.join();
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

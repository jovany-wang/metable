#include "common/logging.h"
#include <fstream>
#include <iostream>

#include "src/protobuf/rpc.grpc.pb.h"
#include "src/common/constants.h"
#include "src/client/metable_client.h"

int main(int argc, char **argv) {
  // Instantiate the client. It requires a channel, out of which the actual RPCs
  // are created. This channel models a connection to an endpoint specified by
  // the argument "--target=" which is the only expected argument.
  // We indicate that the channel isn't authenticated (use of
  // InsecureChannelCredentials()).
  std::string target_str;
  std::string arg_str("--target");
  if (argc > 1) {
    std::string arg_val = argv[1];
    size_t start_pos = arg_val.find(arg_str);
    if (start_pos != std::string::npos) {
      start_pos += arg_str.size();
      if (arg_val[start_pos] == '=') {
        target_str = arg_val.substr(start_pos + 1);
      } else {
        std::cout << "The only correct argument syntax is --target="
                  << std::endl;
        return 0;
      }
    } else {
      std::cout << "The only acceptable argument is --target=" << std::endl;
      return 0;
    }
  } else {
    target_str = "localhost:10001";
  }

  metable::MetableClient metable_client(
      grpc::CreateChannel(target_str, grpc::InsecureChannelCredentials()));
  std::string user("qingwang");
  bool result = metable_client.CheckVersion(user);
  std::cout << "Version matched ==" << result << std::endl;

  /*
      When the versions match,
      You can cancel the following comments about creating test tables.

      if(result) {
          std::cout << "Now creata test table(name='test_meta_table', field0(string, name)): " << std::endl;
          std::string table_name("test_meta_table");
          std::vector<std::pair<std::string, std::string>> vec;
          vec.push_back(std::make_pair("string", "name"));
          bool _result = metable_client.CreateTable(table_name, vec);
          if(_result) {
                std::cout << "create table success, the name is " << result << std::endl;
          } else {
                std::cout << "create table fail!" << std::endl;
          }
      }
  */

  return 0;
}

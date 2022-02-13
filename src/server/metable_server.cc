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

    virtual grpc::Status MetableServiceImpl::CreateTable(::grpc::ServerContext *context,
                                const rpc::CreateTableRequest *request,
                                rpc::CreateTableReply *reply) override {

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
        std::unique_ptr<Server> server(builder.BuildAndStart());
        std::cout << "Server listening on " << server_address << std::endl;

        // Wait for the server to shutdown. Note that some other thread must be
        // responsible for shutting down the server for this call to ever return.
        server->Wait();
    }

} // namespace metable

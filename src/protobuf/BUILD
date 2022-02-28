package(default_visibility = ["//visibility:public"])

load("@rules_proto//proto:defs.bzl", "proto_library")
load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library", "cc_proto_library", "cc_test")
load("@rules_proto_grpc//python:defs.bzl", "python_grpc_compile")

proto_library(
    name = "rpc_proto",
    srcs = ["rpc.proto"],
    deps = [],
    visibility = ["//visibility:public"],
)

cc_proto_library(
    name = "rpc_cc_proto",
    deps = ["rpc_proto"],
)
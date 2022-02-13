package(default_visibility = ["//visibility:public"])

load("@rules_proto//proto:defs.bzl", "proto_library")
load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library", "cc_proto_library", "cc_test")
load("@rules_proto_grpc//python:defs.bzl", "python_grpc_compile")

proto_library(
    name = "hello_proto",
    srcs = ["hello.proto"],
    deps = [],
    visibility = ["//visibility:public"],
)

cc_proto_library(
    name = "hello_cc_proto",
    deps = [":hello_proto"],
)

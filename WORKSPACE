workspace(name = "com_github_jovany_wang_metable")

load("//bazel:metable_deps_setup.bzl", "metable_deps_setup")

metable_deps_setup()

load("//bazel:metable_deps_build_all.bzl", "metable_deps_build_all")

metable_deps_build_all()

# This needs to be run after grpc_deps() in metable_deps_build_all() to make
# sure all the packages loaded by grpc_deps() are available. However a
# load() statement cannot be in a function so we put it here.
load("@com_github_grpc_grpc//bazel:grpc_extra_deps.bzl", "grpc_extra_deps")

grpc_extra_deps()

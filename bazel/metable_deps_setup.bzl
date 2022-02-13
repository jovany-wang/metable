load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository", "new_git_repository")
load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive", "http_file")
load("@bazel_tools//tools/build_defs/repo:utils.bzl", "maybe")
  

def metable_deps_setup():
    maybe(
        http_archive,
        name = "com_github_spdlog",
        sha256 = "1e68e9b40cf63bb022a4b18cdc1c9d88eb5d97e4fd64fa981950a9cacf57a4bf",
        urls = [
            "https://github.com/gabime/spdlog/archive/v1.8.0.tar.gz",
        ],
        strip_prefix = "spdlog-1.8.0",
        build_file = "@com_github_jovany_wang_metable//thirdparty:spdlog.BUILD",
    )

    maybe(
        http_archive,
        name = "com_github_grpc_grpc",
        # NOTE: If you update this, also update @boringssl's hash.
        url = "https://github.com/grpc/grpc/archive/refs/tags/v1.42.0.tar.gz",
        sha256 = "b2f2620c762427bfeeef96a68c1924319f384e877bc0e084487601e4cc6e434c",
        strip_prefix = "grpc-1.42.0",
    )

    maybe(
        http_archive,
        name = "rules_proto_grpc",
        url = "https://github.com/rules-proto-grpc/rules_proto_grpc/archive/a74fef39c5fe636580083545f76d1eab74f6450d.tar.gz",
        sha256 = "2f6606151ec042e23396f07de9e7dcf6ca9a5db1d2b09f0cc93a7fc7f4008d1b",
        strip_prefix = "rules_proto_grpc-a74fef39c5fe636580083545f76d1eab74f6450d",
    )

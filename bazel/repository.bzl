load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:utils.bzl", "maybe")

def metable_deps():
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

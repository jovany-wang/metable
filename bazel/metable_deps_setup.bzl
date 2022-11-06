load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository", "new_git_repository")
load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive", "http_file", "http_jar")
load("@bazel_tools//tools/build_defs/repo:utils.bzl", "maybe")

def metable_deps_setup():
    maybe(
        http_archive,
        name = "platforms",
        urls = [
            "https://mirror.bazel.build/github.com/bazelbuild/platforms/releases/download/0.0.4/platforms-0.0.4.tar.gz",
            "https://github.com/bazelbuild/platforms/releases/download/0.0.4/platforms-0.0.4.tar.gz",
        ],
        sha256 = "079945598e4b6cc075846f7fd6a9d0857c33a7afc0de868c2ccb96405225135d",
    )

    maybe(
        http_archive,
        name = "com_github_spdlog",
        sha256 = "1e68e9b40cf63bb022a4b18cdc1c9d88eb5d97e4fd64fa981950a9cacf57a4bf",
        urls = [
            "https://github.com/gabime/spdlog/archive/v1.8.0.tar.gz",
        ],
        strip_prefix = "spdlog-1.8.0",
        build_file = "@com_github_jovany_wang_metable//bazel/thirdparty:spdlog.BUILD",
    )

    maybe(
        http_archive,
        name = "com_github_grpc_grpc",
        url = "https://github.com/grpc/grpc/archive/refs/tags/v1.43.2.tar.gz",
        sha256 = "b74ce7d26fe187970d1d8e2c06a5d3391122f7bc1fdce569aff5e435fb8fe780",
        strip_prefix = "grpc-1.43.2",
    )

    maybe(
        http_archive,
        name = "rules_proto_grpc",
        url = "https://github.com/rules-proto-grpc/rules_proto_grpc/archive/a74fef39c5fe636580083545f76d1eab74f6450d.tar.gz",
        sha256 = "2f6606151ec042e23396f07de9e7dcf6ca9a5db1d2b09f0cc93a7fc7f4008d1b",
        strip_prefix = "rules_proto_grpc-a74fef39c5fe636580083545f76d1eab74f6450d",
    )

    maybe(
        http_archive,
        name = "com_google_googletest",
        url = "https://github.com/google/googletest/archive/refs/tags/release-1.11.0.tar.gz",
        sha256 = "b4870bf121ff7795ba20d20bcdd8627b8e088f2d1dab299a031c1034eddc93d5",
        strip_prefix = "googletest-release-1.11.0",
    )

    maybe(
        http_archive,
        name = "com_github_gflags_gflags",
        url = "https://github.com/gflags/gflags/archive/refs/tags/v2.2.2.tar.gz",
        sha256 = "34af2f15cf7367513b352bdcd2493ab14ce43692d2dcd9dfc499492966c64dcf",
        strip_prefix = "gflags-2.2.2",
    )

    maybe(
        http_archive,
        name = "com_github_skiplist",
        sha256 = "6d1f85e21eea192490f9ebf58426a184b3ac5cb597b353e544bfc904b5d0855d",
        urls = [
            "https://github.com/greensky00/skiplist/archive/7f44208038857002b83223aeda0321f0f464da6e.tar.gz",
        ],
        strip_prefix = "skiplist-7f44208038857002b83223aeda0321f0f464da6e",
        build_file = "@com_github_jovany_wang_metable//bazel/thirdparty:skiplist.BUILD",
    )

    maybe(
        http_archive,
        name = "asio",
        sha256 = "4cd5cd0ad97e752a4075f02778732a3737b587f5eeefab59cd98dc43b0dcadb3",
        urls = [
            "https://shutian.oss-cn-hangzhou.aliyuncs.com/cdn/asio/asio-1.20.0.tar.gz",
        ],
        strip_prefix = "asio-1.20.0",
        build_file = "@com_github_jovany_wang_metable//bazel/thirdparty:asio.BUILD",
    )

    maybe(
        http_archive,
        name = "rules_antlr",
        sha256 = "26e6a83c665cf6c1093b628b3a749071322f0f70305d12ede30909695ed85591",
        url = "https://github.com/marcohu/rules_antlr/archive/0.5.0.tar.gz",
        strip_prefix = "rules_antlr-0.5.0",
    )

    maybe(
        http_archive,
        name = "antlr4_runtimes",
        sha256 = "efe4057d75ab48145d4683100fec7f77d7f87fa258707330cadd1f8e6f7eecae",
        build_file_content = """
package(default_visibility = ["//visibility:public"])
cc_library(
    name = "cpp",
    srcs = glob(["runtime/Cpp/runtime/src/**/*.cpp"]),
    hdrs = glob(["runtime/Cpp/runtime/src/**/*.h"]),
    includes = ["runtime/Cpp/runtime/src"],
)
 """,
        strip_prefix = "antlr4-4.9.3",
        urls = ["https://github.com/antlr/antlr4/archive/refs/tags/4.9.3.tar.gz"],
    )

    maybe(
        http_jar,
        name = "antlr4_tool",
        sha256 = "386fec520b8962fe37f448af383920ea33d7a532314b36d7ba9ccec1ba95eb37",
        url = "https://repo1.maven.org/maven2/org/antlr/antlr4/4.9.3/antlr4-4.9.3.jar",
    )

    maybe(
        http_jar,
        name = "javax_json",
        sha256 = "17fdeb7e22375a7fb40bb0551306f6dcf2b5743078668adcdf6c642c9a9ec955",
        url = "https://repo1.maven.org/maven2/org/glassfish/javax.json/1.1.4/javax.json-1.1.4.jar",
    )

    maybe(
        http_jar,
        name = "stringtemplate4",
        sha256 = "64503dd855b48edfe0e597494acfb4a481f26a8e254608ad7506d991674f5bce",
        url = "https://repo1.maven.org/maven2/org/antlr/ST4/4.3.3/ST4-4.3.3.jar",
    )

    maybe(
        http_jar,
        name = "antlr4_runtime",
        sha256 = "131a6594969bc4f321d652ea2a33bc0e378ca312685ef87791b2c60b29d01ea5",
        url = "https://repo1.maven.org/maven2/org/antlr/antlr4-runtime/4.9.3/antlr4-runtime-4.9.3.jar",
    )

    maybe(
        http_jar,
        name = "antlr3_runtime",
        sha256 = "68bf9f5a33dfcb34033495c587e6236bef4e37aa6612919f5b1e843b90669fb9",
        url = "https://repo1.maven.org/maven2/org/antlr/antlr-runtime/3.5.3/antlr-runtime-3.5.3.jar",
    )

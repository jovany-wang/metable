load("@rules_antlr//antlr:antlr4.bzl", "antlr")

antlr(
    name = "sql_grammar",
    srcs = [
        "SqlGrammar.g4",
        "SqlLexer.g4",
    ],
    language = "Cpp",
    listener = False,
    package = None,
    visibility = ["//visibility:public"],
    visitor = True,
)

cc_library(
    name = "sql_grammar_parser",
    srcs = ["sql_grammar"],
    linkstatic = 1,
    visibility = ["//visibility:public"],
    deps = [
        "sql_grammar",
        "@antlr4_runtimes//:cpp",
    ],
)

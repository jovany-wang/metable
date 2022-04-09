load("@rules_antlr//antlr:antlr4.bzl", "antlr")

antlr(
    name = "sql_grammer",
    srcs = ["sql.g4"],
    language = "Cpp",
    listener = False,
    visitor = True,
    package = None,
    visibility = ["//visibility:public"],
)

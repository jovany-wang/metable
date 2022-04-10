load("@rules_antlr//antlr:antlr4.bzl", "antlr")

antlr(
    name = "sql_grammar",
    srcs = ["sql_grammar.g4", "sql_lexer.g4"],
    language = "Cpp",
    listener = False,
    visitor = True,
    package = None,
    visibility = ["//visibility:public"],
)

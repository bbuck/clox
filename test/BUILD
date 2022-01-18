# Tests for the C Lox library

cc_test(
    name = "chunk_test",
    srcs = ["chunk_test.c"],
    deps = [
        ":helpers",
        "//:chunk",
        "@user_local//:criterion",
    ],
)

cc_test(
    name = "value_test",
    srcs = ["value_test.c"],
    deps = [
        ":helpers",
        "//:value",
        "@user_local//:criterion",
    ],
)

cc_library(
    name = "helpers",
    srcs = ["helpers.c"],
    hdrs = ["helpers.h"],
    deps = [
        "//:value",
        "@user_local//:criterion",
    ],
)

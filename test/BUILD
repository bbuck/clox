# Tests for the C Lox library

cc_test(
    name = "unit_tests",
    deps = [
        ":chunk_test",
        "@user_local//:criterion",
    ],
)

cc_test(
    name = "chunk_test",
    srcs = ["chunk_test.c"],
    deps = [
        ":helpers",
        "//:chunk",
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

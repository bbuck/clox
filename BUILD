# C Lox binary and supporting libraries.

cc_binary(
    name = "clox",
    srcs = ["main.c"],
    deps = [
        ":chunk",
        ":common",
        ":debug",
    ],
)

cc_library(
    name = "common",
    hdrs = ["common.h"],
)

cc_library(
    name = "chunk",
    srcs = ["chunk.c"],
    hdrs = ["chunk.h"],
    deps = [
        ":common",
        ":memory",
        ":value",
    ],
)

cc_library(
    name = "memory",
    srcs = ["memory.c"],
    hdrs = ["memory.h"],
    deps = [":common"],
)

cc_library(
    name = "debug",
    srcs = ["debug.c"],
    hdrs = ["debug.h"],
    deps = [":chunk"],
)

cc_library(
    name = "value",
    srcs = ["value.c"],
    hdrs = ["value.h"],
    deps = [":memory"],
)

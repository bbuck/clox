# Workspace for the C implementation of Lox

new_local_repository(
    name = "user_local",
    build_file_content = """
cc_import(
    name = "criterion",
    hdrs = ["include/criterion/criterion.h"],
    shared_library = "lib/libcriterion.dylib",
    visibility = ["//visibility:public"],
)
    """,
    path = "/usr/local",
)

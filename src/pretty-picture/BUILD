cc_binary(
    name = "pretty-picture",
    srcs = [
        "main.cc",
    ],
    copts = [
        "-Iinclude", # TODO-jrk: this should be handled by //include/pp:headers
        "-Iexternal/libbmp/CPP"
    ],
    deps = [
        "//include/pp:headers",
        "//src/pp",
        "@libbmp//:main",
    ]
)
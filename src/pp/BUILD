cc_library(
    name = "pp",
    visibility  = ["//visibility:public"],
    deps = [
        "//include/pp:headers",
    ],
    copts = [
        "-Iinclude", # TODO-jrk: this should be handled by //include/pp:headers
    ],
    srcs = [
        "fun/ConstantFunction.cc",
        "fun/CoordinateFunction.cc",
        "fun/IFunction.cc",
        "fun/IFunctionGenerator.cc",
        "fun/NegateFunction.cc",
        "fun/RoundFunction.cc",
    ],
)

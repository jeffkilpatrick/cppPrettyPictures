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
        "Color.cc",
        "Generate.cc",
        "Registry.cc",
        "fun/ArithmeticFunction.cc",
        "fun/ConstantFunction.cc",
        "fun/CoordinateFunction.cc",
        "fun/IFunction.cc",
        "fun/IFunctionGenerator.cc",
        "fun/LogFunction.cc",
        "fun/NegateFunction.cc",
        "fun/RoundFunction.cc",
        "fun/TrigFunction.cc",
    ],
)

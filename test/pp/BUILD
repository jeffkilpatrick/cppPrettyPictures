cc_test(
    name = "fun-test",
    size = "small",
    srcs = [
        "fun/CoordinateFunctionTest.cc",
        "fun/ConstantFunctionTest.cc",
    ],
    copts = [
        "-Iinclude", # TODO-jrk: this should be handled by //include/pp:headers
        "-Iexternal/gtest/include", # TODO-jrk: make @gtest handle this?
    ],
    deps = [
        "//include/pp:headers",
        "//src/pp",
        "@gtest//:main",
    ],
)

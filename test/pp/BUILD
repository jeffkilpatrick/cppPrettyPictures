cc_test(
    name = "fun-test",
    srcs = [
    	"fun/ConstantFunctionTest.cc"
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

cc_test(
    name = "fun-test",
    size = "small",
    srcs = [
        "GenerateTest.cc",
        "RegistryTest.cc",
        "fun/ArithmeticFunctionTest.cc",
        "fun/ColorSpaceFunctionTest.cc",
        "fun/CoordinateFunctionTest.cc",
        "fun/ConstantFunctionTest.cc",
        "fun/InnerProductFunctionTest.cc",
        "fun/LogFunctionTest.cc",
        "fun/NegateFunctionTest.cc",
        "fun/RoundFunctionTest.cc",
        "fun/TrigFunctionTest.cc",
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

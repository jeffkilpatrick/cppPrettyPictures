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
        "fun/DissolveFunctionTest.cc",
        "fun/InnerProductFunctionTest.cc",
        "fun/LogFunctionTest.cc",
        "fun/NegateFunctionTest.cc",
        "fun/NoiseFunctionTest.cc",
        "fun/RoundFunctionTest.cc",
        "fun/TrigFunctionTest.cc",
    ],
    copts = [
    ],
    deps = [
        "//include",
        "//src/pp",
        "@gtest//:main",
    ],
)


cc_test(
    name = "serialize-test",
    size = "small",
    srcs = [
        "serialize/FunctionSerializerTest.cc",
    ],
    copts = [
    ],
    deps = [
        "//include",
        "//src/pp",
        "@gtest//:main",
    ],
)

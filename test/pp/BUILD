cc_test(
    name = "fun-test",
    size = "small",
    srcs = [
        "ImageTest.cc",
        "expr/EvalTest.cc",
        "expr/GenerateTest.cc",
        "fun/ArithmeticFunctionTest.cc",
        "fun/ColorSpaceFunctionTest.cc",
        "fun/CoordinateFunctionTest.cc",
        "fun/ConstantFunctionTest.cc",
        "fun/DissolveFunctionTest.cc",
        "fun/InnerProductFunctionTest.cc",
        "fun/LogFunctionTest.cc",
        "fun/NegateFunctionTest.cc",
        "fun/NoiseFunctionTest.cc",
        "fun/RegistryTest.cc",
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
        "serialize/FunctionParserTest.cc",
        "serialize/FunctionSerializerTest.cc",
        "serialize/ScannerTest.cc",
    ],
    copts = [
    ],
    deps = [
        "//include",
        "//src/pp",
        "@gtest//:main",
    ],
)

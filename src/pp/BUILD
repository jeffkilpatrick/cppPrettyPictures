cc_library(
    name = "pp",
    visibility  = ["//visibility:public"],
    deps = [
        "//include",
        "@boost//:variant",
    ],
    srcs = [
        "Color.cc",
        "Generate.cc",
        "Registry.cc",
        "fun/ArithmeticFunction.cc",
        "fun/ConstantFunction.cc",
        "fun/ColorSpaceFunction.cc",
        "fun/CoordinateFunction.cc",
        "fun/DissolveFunction.cc",
        "fun/IFunction.cc",
        "fun/IFunctionGenerator.cc",
        "fun/InnerProductFunction.cc",
        "fun/LogFunction.cc",
        "fun/NegateFunction.cc",
        "fun/NoiseFunction.cc",
        "fun/RoundFunction.cc",
        "fun/TrigFunction.cc",
        "serialize/FunctionSerializer.cc",
        "serialize/Scanner.cc",
        "serialize/Token.cc",
    ],
)

genrule(
    name = "Scanner.cc",
    srcs = [ "serialize/Scanner.re" ],
    outs = [ "serialize/Scanner.cc" ],
    cmd = "re2c $< --output $@"
)

cc_library(
    name = "pp",
    visibility  = ["//visibility:public"],
    copts = [ "-Werror", "-Wall" ],
    deps = [
        "//include",
        "@boost//:variant",
        "@libbmp//:main",
        "@lodepng//:main",
    ],
    srcs = [
        "Color.cc",
        "Eval.cc",
        "Export.cc",
        "Generate.cc",
        "Image.cc",
        "Registry.cc",
        "fun/ConstantFunction.cc",
        "fun/ColorSpaceFunction.cc",
        "fun/IFunction.cc",
        "fun/IFunctionGenerator.cc",
        "fun/InnerProductFunction.cc",
        "fun/NoiseFunction.cc",
        "serialize/FunctionParser.cc",
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

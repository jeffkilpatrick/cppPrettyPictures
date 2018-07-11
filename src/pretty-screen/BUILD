load(
    "@build_bazel_rules_apple//apple:macos.bzl",
    "macos_bundle",
)

load(
    "@build_bazel_rules_apple//apple:versioning.bzl",
    "apple_bundle_version",
)

objc_library(
    name = "Sources",
    sdk_frameworks = [
        "ScreenSaver",
    ],
    deps = [
        "//include",
        "//src/pp",
    ],
    srcs = [
        "PrettyScreenView.h",
        "PrettyScreenView.mm",
    ],
)

apple_bundle_version(
    name = "PrettyScreenVersion",
    build_version = "1.0",
)

macos_bundle(
    name = "PrettyScreen",
    bundle_id = "org.bouncingsheep.PrettyScreen",
    infoplists = [":Info.plist"],
    bundle_extension = "saver",
    minimum_os_version = "10.13",
    version = ":PrettyScreenVersion",
    deps = [
        ":Sources",
    ],
)

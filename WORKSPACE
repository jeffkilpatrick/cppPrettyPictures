git_repository(
    name = "com_github_nelhage_rules_boost",
    commit = "239ce40e42ab0e3fe7ce84c2e9303ff8a277c41a",
    remote = "https://github.com/nelhage/rules_boost",
)

load("@com_github_nelhage_rules_boost//:boost/boost.bzl", "boost_deps")
boost_deps()

new_http_archive(
    name = "gtest",
    url = "https://github.com/google/googletest/archive/release-1.7.0.zip",
    sha256 = "b58cb7547a28b2c718d1e38aee18a3659c9e3ff52440297e965f5edffe34b6d0",
    build_file = "gtest.BUILD",
    strip_prefix = "googletest-release-1.7.0",
)

new_http_archive(
    name = "libbmp",
    url = "https://github.com/marc-q/libbmp/archive/66bec6d7daf254e6dc07d55c9383fd68276a6a39.zip",
    sha256 = "b581a402ea9288d5e07a228eb0ef6f6035961aaad96805050a27e8b79b4e57ba",
    build_file = "libbmp.BUILD",
    strip_prefix = "libbmp-66bec6d7daf254e6dc07d55c9383fd68276a6a39",
)

new_http_archive(
    name = "lodepng",
    url = "https://github.com/lvandeve/lodepng/archive/81cf5de55f7eb3b5bf9116400a8adc050bde6633.zip",
    sha256 = "10202d27037b2b70cdfb72fcc7c9e850b48ba1b865ff599aba6bcac5277c3965",
    build_file = "lodepng.BUILD",
    strip_prefix = "lodepng-81cf5de55f7eb3b5bf9116400a8adc050bde6633",
)

git_repository(
    name = "build_bazel_rules_apple",
    remote = "https://github.com/bazelbuild/rules_apple.git",
    tag = "0.6.0",
)

load(
    "@build_bazel_rules_apple//apple:repositories.bzl",
    "apple_rules_dependencies",
)
apple_rules_dependencies()

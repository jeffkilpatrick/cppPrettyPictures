# Pretty Pictures (C++ Edition)

This is a partial implementation of Sims K. _Artificial Evolution for Computer
Graphics_. Computer Graphics, 25(4), July 1991, pp. 319-328. That is to say,
it creates randomly-generated pretty pictures. It comes in three flavors:
* `PrettyViewer` as a simple standalone macOS application that shows a
  randomly generated picture. Recycle the process to see a new one.
* `pretty-picture` is a CLI utility to render a randomly generated or
  user-specified image expression to PNG.
* `pretty-screen` is a macOS screen saver.

# Requirements
* Up-to-date macOS, Xcode
* `gtest` -- check out this repo with `--recurse-submodules`.
* `libpng` -- expected to be found in `/usr/local/include` and
  `/usr/local/lib`.
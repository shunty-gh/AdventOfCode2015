# Advent of Code 2015

Some code to help solve the [Advent of Code 2015](https://adventofcode.com/2015)) problems. The early days were written during the 2015 AoC period but the later ones were done several years later when I decided it was time to finish it all off properly.

## C#

`*.linq` files are [LINQPad](https://www.linqpad.net/) scripts written in C# with .Net Framework 4.x but mostly all work fine with .Net Core too. As the scripts use LINQPad they are Windows only.

## Python
There are a couple of `Python` scripts written using Python 3 but work OK with Python 2 too. Cross platform of course.

## C++
`*.cpp` C++, cross platform code, written using mainly [Visual Studio Code](https://code.visualstudio.com/), targeting C++17. Written primarily using the Microsoft C++ compiler (v19.x) but also trying to make sure it builds fine using `g++` (v9 and 10) and `clang++` (v11) on Windows, [WSL2](https://docs.microsoft.com/en-us/windows/wsl/) and Linux.

`g++` and `clang++` on Windows used the builds from [MSYS2](https://www.msys2.org/) and the binaries from [the LLVM downloads page](https://releases.llvm.org/download.html).

### Compile on Linux
The make files `Makefile` and `Makefile.msvc` are for building Windows executables (using g++ and MSVC respectively). The appropriate incantation for Linux/WSL is something along the lines of:

```
$> g++ -std=c++17 -g -o aoc2015 src/*.cpp
OR
$> clang++ -std=c++17 -g -o aoc2015 src/*.cpp
```
or, for optimised builds, something like, eg
```
$> g++ -std=c++17 -O2 -o aoc2015 src/*.cpp
```

### Debug
Debugging in VSCode works best when using the MSVC build tools, but make sure that VSCode is started from within the `Developer Command Prompt` - using something like:
```
$> code .
```
so that all the MSVC paths and include dirs etc are set correctly.

The g++ and clang++ settings for VSCode are included but I had issues with it trying to display contents of things like vectors and maps. YMMV.

### Command line params
The compiled C++ program will run solutions for all days (from day 14 onward) if started without command line parameters but one or more specific days can be run with the use of the `-d` flag. eg:

```
$> aoc2015.exe -d 15
```
or
```
$> aoc2015.exe -d 17,20,22
```
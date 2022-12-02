cmake_minimum_required(VERSION 3.10)

# set the project name
project(test)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_CLANG_TIDY "clang-tidy-mp-15;-checks=-*,clang-*,cppcoreguidelines-*,-cppcoreguidelines-avoid-magic-numbers,performance-*,-cppcoreguidelines-pro-bounds-array-to-pointer-decay,llvm-*,modernize-*,-modernize-use-trailing-return-type,cert-*")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


# add the executable
add_executable(test main.cpp Intervals.hh bitwiseNot.hh bitwiseNot.cpp bitwiseOr.hh bitwiseOr.cpp bitwiseAnd.hh bitwiseAnd.cpp bitwiseXOr.hh bitwiseXOr.cpp bitwiseOperations.cpp bitwiseOperations.hh)



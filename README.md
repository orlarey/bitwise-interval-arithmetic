![C/C++ CI](https://github.com/orlarey/cpptemplate/workflows/C/C++%20CI/badge.svg)

# Bitwise Operations on Intervals
This small library provides exact bitwise operations on integer intervals. The results are exact in the sense that they are the same than a brute-force implementation, but faster. Integer intervals can be either signed (`SInterval`) or unsigned (`UInterval`). 

The four operations are:

- NOT: `bitwiseUnsignedNot()` or `bitwiseSignedNot()`
- OR: `bitwiseUnsignedOr()` or `bitwiseSignedOr()`
- AND: `bitwiseUnsignedAnd()` or `bitwiseSignedAnd()`
- XOR: `bitwiseUnsignedXOr()` or `bitwiseSignedXOr()`

Only NOT and OR are really implemented. AND and XOR operations are implemented by De Morgan equivalences.

The implementation is in two files `bitwiseOperations.hh,.cpp`. All the other files implements the brute force methods and the tests. 

The random tests are implemented in `main.cpp`.

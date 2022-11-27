#pragma once

// We need signed and unsigned numbers. But in order to test with brute force
// the various algorithm in a limited amount of time, we can use full ints.

// Numbers we are going to use
#define SNUM char
#define UNUM unsigned char

// and their limits
#define SNUM_MAX 127
#define SNUM_MIN -128
#define UNUM_MAX 255
#define UNUM_MIN 0

// Because we are not using ints we will need often to cast ints to signed of unsigned nums
template <typename T>
constexpr SNUM snum(T x)
{
    return (SNUM)(x);
}

template <typename T>
constexpr UNUM unum(T x)
{
    return (UNUM)(x);
}

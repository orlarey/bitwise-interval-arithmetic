#include <iostream>
#include <random>

#include "Intervals.hh"
#include "Numbers.hh"

static std::random_device                                       dev;
static std::mt19937                                             rng(dev());
static std::uniform_int_distribution<std::mt19937::result_type> randomUNUM(0, UNUM_MAX);
static std::uniform_int_distribution<std::mt19937::result_type> randomSNUM(SNUM_MIN, SNUM_MAX);

UInterval urandom()
{
    UNUM x = randomUNUM(rng);
    UNUM y = randomUNUM(rng);

    if (x <= y) return UInterval{x, y};
    return UInterval{y, x};
}

SInterval srandom()
{
    SNUM x = randomSNUM(rng);
    SNUM y = randomSNUM(rng);

    if (x <= y) return SInterval{x, y};
    return SInterval{y, x};
}
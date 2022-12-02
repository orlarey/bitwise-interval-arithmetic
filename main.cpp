
#include <iostream>
#include <memory>
#include <random>
#include <sstream>
#include <string>

#include "bitwiseAnd.hh"
#include "bitwiseNot.hh"
#include "bitwiseOperations.hh"
#include "bitwiseOr.hh"
#include "bitwiseXOr.hh"

// generate random intervals for test purposes
using namespace itv;

constexpr int N          = 100;
constexpr int TEST_LIMIT = 4096;

class RandomIntervals
{
    std::unique_ptr<std::mt19937> rng;

    std::uniform_int_distribution<std::mt19937::result_type> udist;
    std::uniform_int_distribution<std::mt19937::result_type> sdist;

   public:
    RandomIntervals() : udist(0, 2 * TEST_LIMIT + 1), sdist(-TEST_LIMIT - 1, TEST_LIMIT)
    {
        std::random_device rd;
        rng = std::make_unique<std::mt19937>(rd());
    }
    SInterval srandom() { return {static_cast<int>(sdist(*rng)), static_cast<int>(sdist(*rng))}; }
    UInterval urandom() { return {static_cast<unsigned int>(udist(*rng)), static_cast<unsigned int>(udist(*rng))}; }
};

int main()
{
    RandomIntervals R;
    bool            g = true;

    std::cout << "BITWISE OPERATIONS ON INTERVALS" << std::endl;

    std::cout << "testUnsignedOr : ";
    g = true;
    for (int i = 0; i < N; i++) g &= testUnsignedOr(R.urandom(), R.urandom());
    if (g) std::cout << "PASS" << std::endl;

    std::cout << "testSignedOr   : ";
    g = true;
    for (int i = 0; i < N; i++) g &= testSignedOr(R.srandom(), R.srandom());
    if (g) std::cout << "PASS" << std::endl;

    std::cout << "testUnsignedAnd: ";
    g = true;
    for (int i = 0; i < N; i++) g &= testUnsignedAnd(R.urandom(), R.urandom());
    if (g) std::cout << "PASS" << std::endl;

    std::cout << "testSignedAnd  : ";
    g = true;
    for (int i = 0; i < N; i++) g &= testSignedAnd(R.srandom(), R.srandom());
    if (g) std::cout << "PASS" << std::endl;

    std::cout << "testUnsignedXOr: ";
    g = true;
    for (int i = 0; i < N; i++) g &= testUnsignedXOr(R.urandom(), R.urandom());
    if (g) std::cout << "PASS" << std::endl;

    std::cout << "testSignedXOr  : ";
    g = true;
    for (int i = 0; i < N; i++) g &= testSignedXOr(R.srandom(), R.srandom());
    if (g) std::cout << "PASS" << std::endl;

    return 0;
}


#include <iostream>
#include <memory>
#include <random>
#include <sstream>
#include <string>

#include "bitwiseAnd.hh"
#include "bitwiseIntervals.hh"
#include "bitwiseNot.hh"
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
    SInterval srandom() { return {(int)(sdist(*rng)), (int)(sdist(*rng))}; }
    UInterval urandom() { return {udist(*rng), udist(*rng)}; }
};

int main()
{
    RandomIntervals R;

    std::cout << "\n--BITWISE OPERATIONS ON INTERVALS TESTS--\n" << std::endl;

    std::cout << "\ntestUnsignedOr" << std::endl;
    for (int i = 0; i < N; i++) testUnsignedOr(R.urandom(), R.urandom());

    std::cout << "\ntestSignedOr" << std::endl;
    for (int i = 0; i < N; i++) testSignedOr(R.srandom(), R.srandom());

    std::cout << "\ntestUnsignedAnd" << std::endl;
    for (int i = 0; i < N; i++) testUnsignedAnd(R.urandom(), R.urandom());

    std::cout << "\ntestSignedAnd" << std::endl;
    for (int i = 0; i < N; i++) testSignedAnd(R.srandom(), R.srandom());

    std::cout << "\ntestUnsignedXOr" << std::endl;
    for (int i = 0; i < N; i++) testUnsignedXOr(R.urandom(), R.urandom());

    std::cout << "\ntestSignedXOr" << std::endl;
    for (int i = 0; i < N; i++) testSignedXOr(R.srandom(), R.srandom());

    return 0;
}


#include <iostream>
#include <sstream>
#include <string>

#include "bitwiseAnd.hh"
#include "bitwiseNot.hh"
#include "bitwiseOr.hh"
#include "random.hh"

void testSignSplit(SNUM lo, SNUM hi)
{
    SInterval a{lo, hi};
    auto [np, pp] = signSplit(a);
    SInterval r   = signMerge(np, pp);

    std::cout << "signSplit(" << a << ") = " << np << ", " << pp << " --merge-> " << r << std::endl;
}

int main()
{
    std::cout << "\n--BITWISE OR TESTS--\n" << std::endl;

    std::cout << "former errors that should be solved" << std::endl;
    testSignedOr(59, 69, 45, 57);
    testSignedOr(35, 114, 21, 108);
    testSignedOr(60, 114, 16, 124);
    testSignedOr(67, 87, 9, 109);

    // std::cout << "urandom()" << std::endl;
    // for (int i = 0; i < 10; i++) std::cout << urandom() << std::endl;
    // std::cout << "srandom()" << std::endl;
    // for (int i = 0; i < 10; i++) std::cout << srandom() << std::endl;
    // std::cout << "\ntestUnsignedNot\n" << std::endl;

    // std::cout << "testUnsignedNot" << std::endl;
    // for (int i = 0; i < 10; i++) testUnsignedNot(urandom());

    // std::cout << "testSignedNot" << std::endl;
    // for (int i = 0; i < 10; i++) testSignedNot(srandom());

    std::cout << "testUnsignedOr" << std::endl;
    for (int i = 0; i < 10; i++) testUnsignedOr(urandom(), urandom());

    std::cout << "testSignedOr" << std::endl;
    for (int i = 0; i < 10; i++) testSignedOr(srandom(), srandom());

    std::cout << "testUnsignedAnd" << std::endl;
    for (int i = 0; i < 10; i++) testUnsignedAnd(urandom(), urandom());

    std::cout << "testSignedAnd" << std::endl;
    for (int i = 0; i < 10; i++) testSignedAnd(srandom(), srandom());

    return 0;
}

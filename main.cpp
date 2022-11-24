
#include <iostream>
#include <sstream>
#include <string>

#include "appear.hh"
#include "bitwiseNot.hh"
#include "bitwiseOr.hh"

int main()
{
    std::cout << "\n--BITWISE OR TESTS--\n" << std::endl;
    std::cout << "testUnsignedNot\n" << std::endl;

    testUnsignedNot(0, 0);
    testUnsignedNot(0, 127);
    testUnsignedNot(0, 128);
    testUnsignedNot(10, 12);

    std::cout << "\n----------------" << std::endl;
    std::cout << "testSignedNot\n" << std::endl;

    testSignedNot(0, 0);
    testSignedNot(0, 127);
    testSignedNot(0, 128);
    testSignedNot(10, 12);

    testSignedNot(-3, 127);
    testSignedNot(-3, 128);
    testSignedNot(-3, 12);

    // std::cout << "\n----------------" << std::endl;
    // std::cout << "testOldUnsignedOr\n" << std::endl;
    // testUnsignedOr({0, 0xffff}, {0xff, 0xfff});
    // std::cout << "\n----------------" << std::endl;

    std::cout << "\n----------------" << std::endl;
    std::cout << "testNewUnsignedOr\n" << std::endl;
    testUnsignedOr(0, 0xffff, 0xff, 0xfff);

    testUnsignedOr(10, 15, 0, 125);
    testUnsignedOr(10, 15, 0, 126);
    testUnsignedOr(10, 15, 0, 127);

    testUnsignedOr(0, 5, 0, 125);
    testUnsignedOr(0, 5, 0, 126);
    testUnsignedOr(0, 5, 0, 127);

    std::cout << "\n----------------" << std::endl;
    std::cout << "testNewSignedOr\n" << std::endl;
    // testSignedOr(-10, -5, 0, 127);
    testSignedOr(-10, 5, 3, 127);
    testSignedOr(-10, 5, -3, 127);
    // testSignedOr(-10, 5, 0, 0xFFFFF);

    // testUnsignedOr(0, 0xffff, 0xff, 0xfff);
    // unsigned int r = hiOr2({0, 0xffff}, {0xff, 0xfff});
    // std::cout << "hiOr2({0, 0xfff}, {0xf, 0xff}) -> " << r << std::endl;

    // std::cout << "\n----------------" << std::endl;
    // std::cout << "testSignedOr\n" << std::endl;

    //    testSignedOr(-10, 5, -10, 5);
    //    testSignedOr(-2, -1, -8, -4);

    return 0;
}

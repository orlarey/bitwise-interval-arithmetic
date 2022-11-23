
#include <iostream>
#include <sstream>
#include <string>

#include "appear.hh"
#include "bwor.hh"
#include "negation.hh"
#include "newand.hh"
#include "newor.hh"

void bruteforceAnd(int lox, int hix, int loy, int hiy)
{
    // Value of INT_MAX is + 2147483647. Value of INT_MIN is - 2147483648.
    int loz = 2147483647;
    int hiz = -2147483648;
    for (int x = lox; x <= hix; x++) {
        for (int y = loy; y <= hiy; y++) {
            int z = x & y;
            if (z > hiz) hiz = z;
            if (z < loz) loz = z;
        }
    }
    std::cout << "Bruteforce (" << lox << ".." << hix << ", " << loy << ".." << hiy << ") -> " << loz << ".." << hiz
              << std::endl;
}

void smartforce2(int lox, int hix, int loy, int hiy)
{
    // check trivial cases
    if (lox == hix && loy == hiy) {
        std::cout << "Smartforce2(" << lox << ".." << hix << ", " << loy << ".." << hiy << ") -> " << (lox & loy) << " "
                  << (lox & loy) << std::endl;
        return;
    }

    if (lox >= 0 && loy >= 0) {
        std::cout << "smartforce2(" << lox << ".." << hix << ", " << loy << ".." << hiy << ") -> ";
        // we are in the simple case
        int z = 0;
        for (int i = 30; i >= 0; i--) {
            int b = 1 << i;

            // is this bit can appear both in x and y interval ?
            bool inx = ((b & hix) != 0) || ((b & lox) != 0) || ((b + lox) <= hix);
            bool iny = ((b & hiy) != 0) || ((b & loy) != 0) || ((b + loy) <= hiy);

            // std::cout << "smartforce2: "
            //           << " i = " << i << " inx = " << inx << " iny = " << iny << std::endl;

            if (inx && iny) {
                // std::cout << "smartforce2: "
                //           << " i = " << i << " is in result " << iny << std::endl;
                // Cette valeur est dans les deux intervals
                // elle doit donc être dans le résultat
                z   = z + b;
                hix = hix - b;
                lox = std::max(0, lox - b);
                hiy = hiy - b;
                loy = std::max(0, loy - b);
            }
        }
        std::cout << 0 << ".." << z << std::endl;
    } else {
        std::cout << "error" << std::endl;
    }
}

// Ne marche pas. contre-exemple : smartforce3(259..259, 0..259) -> 0 0 au lieu de 0 259
void smartforce3(int lox, int hix, int loy, int hiy)
{
    // Value of INT_MAX is + 2147483647. Value of INT_MIN is - 2147483648.
    if (lox >= 0 && loy >= 0) {
        std::cout << "smartforce3(" << lox << ".." << hix << ", " << loy << ".." << hiy << ") -> ";
        // we are in the simple case
        int z = 0;
        for (int i = 30; i >= 0; i--) {
            int b = 1 << i;

            // is this bit can appear both in x and y interval ?
            // bool inx = b >= lox && b <= hix;
            // bool iny = b >= loy && b <= hiy;

            // is this bit can appear both in x and y interval ?
            bool inx = ((b & hix) != 0) || ((b & lox) != 0) || ((b + lox) <= hix);
            bool iny = ((b & hiy) != 0) || ((b & loy) != 0) || ((b + loy) <= hiy);

            // std::cout << "smartforce2: "
            //           << " i = " << i << " inx = " << inx << " iny = " << iny << std::endl;

            if (inx && iny) {
                // std::cout << "smartforce2: "
                //           << " i = " << i << " is in result " << iny << std::endl;
                // Cette valeur est dans les deux intervals
                // elle doit donc être dans le résultat
                z = z + b;

                // we can remove this bit from the intervals
                hix = hix - b;
                lox = std::max(0, lox - b);
                hiy = hiy - b;
                loy = std::max(0, loy - b);
            }
        }
        std::cout << 0 << ".." << z << std::endl;
    } else {
        std::cout << "error" << std::endl;
    }
}

// true if the bit b is always 1 in the interval [lox..hix]
bool alwaysin(int b, int lo, int hi)
{
    int v = 1 << b;
    return (v & lo) && (v > hi - lo);
}

// Ne marche pas. contre-exemple : smartforce3(259..259, 0..259) -> 0 0 au lieu de 0 259
void smartforce4(int lox, int hix, int loy, int hiy)
{
    // Value of INT_MAX is + 2147483647. Value of INT_MIN is - 2147483648.
    if (lox >= 0 && loy >= 0) {
        // we are in the simple case

        std::cout << "smartforce4(" << lox << ".." << hix << ", " << loy << ".." << hiy << ") -> ";

        // compute the minimum value
        int w = 0;
        for (int b = 30; b >= 0; b--) {
            if (alwaysin(b, lox, hix) && alwaysin(b, loy, hiy)) {
                w = w + (1 << b);
            }
        }

        // compute the maximum value
        int z = 0;
        for (int i = 30; i >= 0; i--) {
            int b = 1 << i;

            // is this bit can appear both in x and y interval ?
            bool inx = (b & lox) || (b >= lox && b <= hix);
            bool iny = (b & loy) || (b >= loy && b <= hiy);

            // std::cout << "smartforce2: "
            //           << " i = " << i << " inx = " << inx << " iny = " << iny << std::endl;

            if (inx && iny) {
                // std::cout << "smartforce2: "
                //           << " i = " << i << " is in result " << iny << std::endl;
                // Cette valeur est dans les deux intervals
                // elle doit donc être dans le résultat
                z = z + b;

                // we can remove this bit from the intervals
                hix = hix - b;
                lox = std::max(0, lox - b);
                hiy = hiy - b;
                loy = std::max(0, loy - b);
            }
        }

        std::cout << w << ".." << z << std::endl;
    } else {
        std::cout << "error" << std::endl;
    }
}

int highest(int lox, int hix, int loy, int hiy)
{
    // compute the maximum value
    int z = 0;
    for (int i = 30; i >= 0; i--) {
        int b = 1 << i;

        // is this bit can appear both in x and y interval ?
        // bool inx = (b & lox) || (b >= lox && b <= hix);
        // bool iny = (b & loy) || (b >= loy && b <= hiy);

        bool inx = ((b & hix) != 0) || ((b & lox) != 0) || ((b + lox) <= hix);
        bool iny = ((b & hiy) != 0) || ((b & loy) != 0) || ((b + loy) <= hiy);

        // std::cout << "smartforce2: "
        //           << " i = " << i << " inx = " << inx << " iny = " << iny << std::endl;

        if (inx && iny) {
            // std::cout << "smartforce2: "
            //           << " i = " << i << " is in result " << iny << std::endl;
            // Cette valeur est dans les deux intervals
            // elle doit donc être dans le résultat
            z = z + b;

            // we can remove this bit from the intervals
            hix = hix - b;
            lox = std::max(0, lox - b);
            hiy = hiy - b;
            loy = std::max(0, loy - b);
        }
    }
    return z;
}

int lowest(int lox, int hix, int loy, int hiy)
{
    // compute the minimum value
    int z = 0;
    for (int i = 30; i >= 0; i--) {
        bool ax = alwaysin(i, lox, hix);
        bool ay = alwaysin(i, loy, hiy);
        if (ax && ay) {
            int b = 1 << i;
            z     = z + b;
            lox   = lox - b;
            loy   = loy - b;
            hix   = hix - b;
            hiy   = hiy - b;
        }
    }
    return z;
}

void smartforce5(int lox, int hix, int loy, int hiy)
{
    int hiz = highest(lox, hix, loy, hiy);
    int loz = lowest(lox, hix, loy, hiy);
    std::cout << "smartforce5(" << lox << ".." << hix << ", " << loy << ".." << hiy << ") -> " << loz << ".." << hiz
              << std::endl;
}

void smartforce6(int lox, int hix, int loy, int hiy)
{
    UInterval r = newUnsignedAnd({lox, hix}, {loy, hiy});
    std::cout << "smartforce6(" << lox << ".." << hix << ", " << loy << ".." << hiy << ") -> " << r << std::endl;
}

void test(int lox, int hix, int loy, int hiy)
{
    std::cout << std::endl;
    bruteforceAnd(lox, hix, loy, hiy);
    smartforce6(lox, hix, loy, hiy);

    // smartforce(lox, hix, loy, hiy);
    smartforce2(lox, hix, loy, hiy);
    // smartforce3(lox, hix, loy, hiy); // ne marche pas
    smartforce4(lox, hix, loy, hiy);
    smartforce5(lox, hix, loy, hiy);
}

void hello()
{
    std::cout << "bitand test" << std::endl;
}

int main()
{
    hello();
    // test(256, 257, 127, 127);
    // test(256, 257, 125, 128);
    // test(256, 257, 0, 128);
    // test(0, 257, 125, 128);
    // test(0, 257, 0, 258);
    // test(259, 259, 0, 259);
    // test(259, 259, 255, 256);
    // test(259, 259, 255, 255);
    // test(1, 2, 1, 3);    // OK
    // test(1, 2, 3, 3);    // Faux
    // test(2, 4, 6, 6);    // Faux
    // test(4, 8, 12, 12);  // Faux
    // test(4, 8, 12, 13);  // Faux
    // test(4, 8, 3, 3);    // Faux

    testS2U2S({0, 127});
    testS2U2S({-10, -5});
    testS2U2S({-10, 5});

    testSignedOr({-10, -5}, {0, 125});
    testSignedOr({-10, -5}, {0, 127});
    testSignedOr({-10, 5}, {0, 127});
    std::cout << std::endl;
    testSignedOr({-10, 5}, {-10, 5});
    testSignedOr({-2, -1}, {-8, -4});
    // std::cout << std::endl;
    // testSignedOr({-10, -1}, {-10, -1});
    // testSignedOr({-10, -1}, {0, 5});
    // testSignedOr({0, 5}, {-10, -1});
    // testSignedOr({0, 5}, {0, 5});

#if 0
    testnegation(-1, 3);
    testnegation(0, 2);
    testnegation(-5, -2);
    testnegation(-5, 5);

    UInterval a(2, 3);
    UInterval b(0, 0);
    UInterval c(0, 0);

    testSplitInterval({2, 3});
    testSplitInterval({1, 3});
    testSplitInterval({15, 126});

    testor(5, 7, 3, 7);
    testor(0, 5, 0, 4);
    testor(0, 6, 3, 4);
    testor(4, 5, 2, 4);
    testor(1, 7, 2, 7);
    testor(2, 3, 4, 8);

    // testor(1000,70000,200,70000);

    // testappear(1, 0, 6);
    // testappear(0, 0, 6);
    // testappear(0, 4, 4);
    // testappear(7, 4, 4);
    // testappear(7, -2, -1);
    // testappear(0, -4, -2);
    // testappear(1, -4, -3);
#endif

    return 0;

    /*
    01 11 = 01
    10 11 = 10

     X   Y  =  Z
    010 110 = 010
    011 110 = 010
    100 110 = 100

     2   6  =  2
     3   6  =  2
     4   6  =  4

     0100 0011 = 1000
     1000 0011 = 1000

    xx yy = zz

    1000
    0100
    0010


    */
}

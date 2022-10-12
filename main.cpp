
#include <iostream>
#include <sstream>
#include <string>

void bruteforce(int lox, int hix, int loy, int hiy)
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
    std::cout << "Bruteforce(" << lox << ".." << hix << ", " << loy << ".." << hiy << ") -> " << loz << " " << hiz
              << std::endl;
}

void smartforce2(int lox, int hix, int loy, int hiy)
{
    // Value of INT_MAX is + 2147483647. Value of INT_MIN is - 2147483648.
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
        std::cout << 0 << " " << z << std::endl;
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
            bool inx = b >= lox && b <= hix;
            bool iny = b >= loy && b <= hiy;

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
        std::cout << 0 << " " << z << std::endl;
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

        std::cout << w << " " << z << std::endl;
    } else {
        std::cout << "error" << std::endl;
    }
}

void test(int lox, int hix, int loy, int hiy)
{
    std::cout << std::endl;
    bruteforce(lox, hix, loy, hiy);
    // smartforce(lox, hix, loy, hiy);
    smartforce2(lox, hix, loy, hiy);
    // smartforce3(lox, hix, loy, hiy); // ne marche pas
    smartforce4(lox, hix, loy, hiy);
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
    test(1, 2, 1, 3);  // OK
    test(1, 2, 3, 3);  // Faux
    return 0;
}

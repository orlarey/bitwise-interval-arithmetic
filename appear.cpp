
#include <iostream>
#include <sstream>
#include <string>

#include "appear.hh"

void brutappear(int b, int lox, int hix)
{
    bool found = false;
    int  v     = 1 << b;
    for (int x = lox; x <= hix; x++) {
        if ((x & v) != 0) {
            found = true;
            break;
        }
    }
    std::cout << "brutappear (" << b << ", " << lox << ".." << hix << ") = " << found << std::endl;
}

/**
 * @brief smartappear, marche très bien pour tous les intervalles.
 *
 * @param lox
 * @param hix
 */
void smartappear(int b, int lox, int hix)
{
    int  v     = 1 << b;
    bool found = ((lox & v) != 0) || ((hix & v) != 0) || (hix - lox >= v);
    std::cout << "smartappear(" << b << ", " << lox << ".." << hix << ") = " << found << std::endl;
}

void testappear(int b, int lox, int hix)
{
    brutappear(b, lox, hix);
    smartappear(b, lox, hix);
}

#include <iostream>
#include <sstream>
#include <string>

#include "negation.hh"

void brutnegation(int lox, int hix)
{
    int loz = 0;
    int hiz = 0;
    for (int x = lox; x <= hix; x++) {
        int z = ~x;
        if (x == lox) {
            loz = z;
            hiz = z;
        } else {
            if (z < loz) loz = z;
            if (z > hiz) hiz = z;
        }
    }
    std::cout << "brutnegation (" << lox << ".." << hix << ") = " << loz << ".." << hiz << std::endl;
}

/**
 * @brief smartnegation, marche très bien pour tous les intervalles.
 *
 * @param lox
 * @param hix
 */
void smartnegation(int lox, int hix)
{
    int loz = ~hix;
    int hiz = ~lox;
    std::cout << "smartnegation(" << lox << ".." << hix << ") = " << loz << ".." << hiz << std::endl;
}

void testnegation(int lox, int hix)
{
    brutnegation(lox, hix);
    smartnegation(lox, hix);
}
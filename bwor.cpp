#include <iostream>
#include <sstream>
#include <string>

#include "bwor.hh"

#include "newor.hh"

void brutor(int lox, int hix, int loy, int hiy)
{
    // Value of INT_MAX is + 2147483647. Value of INT_MIN is - 2147483648.
    int loz = 2147483647;
    int hiz = -2147483648;
    for (int x = lox; x <= hix; x++) {
        for (int y = loy; y <= hiy; y++) {
            int z = x | y;
            if (z > hiz) hiz = z;
            if (z < loz) loz = z;
        }
    }
    std::cout << "Brutor (" << lox << ".." << hix << ", " << loy << ".." << hiy << ") -> " << loz << ".." << hiz
              << std::endl;
}

/**
 * @brief smartor, marche très bien pour tous les intervalles.
 * Dans un ou on ajoute des bits on ne peut jamais en enlever.
 * Pae consequent si :
 * 	[x0..x1] or [y0..y1] = [z0..z1]
 *  alors z1 >= max(x1, y1) et z0 >= max(x0, y0)
 *
 * @param lox
 * @param hix
 */
// Cette stratégie ne marche pas ni pour lo ni pour hi
// Brutor (2..3, 4..8) -> 6..11
// Smartor(2..3, 4..8) -> 4..11
// Brutor (4..5, 2..4) -> 4..7
// Smartor(4..5, 2..4) -> 4..5

void smartor(int lox, int hix, int loy, int hiy) 
{
    int loz = std::max(lox, loy);  // ne peut pas être plus petit que le plus grand des plus petits
    int hiz = hix | hiy;           // ne peut pas être plus petit que le plus grand des plus grands

    std::cout << "Smartor(" << lox << ".." << hix << ", " << loy << ".." << hiy << ") -> " << loz << ".." << hiz
              << std::endl;
}

void testor(int lox, int hix, int loy, int hiy)
{
    brutor(lox, hix, loy, hiy);
    smartor(lox, hix, loy, hiy);
    auto z = newor({lox, hix}, {loy, hiy});
    std::cout << "Newor  (" << lox << ".." << hix << ", " << loy << ".." << hiy << ") -> " << z
              << '\n' << std::endl;
}
#include <iostream>  // std::cout
#include <string>    // std::string
#include <utility>   // std::pair, std::make_pair

typedef std::pair<unsigned int, unsigned int> UInterval;

// return the union of two intervals
UInterval operator+(const UInterval& a, const UInterval& b);

// msb: most significant bit
unsigned int msb32(unsigned int x);

bool canSplitInterval(UInterval x, UInterval& a, UInterval& b);
void testSplitInterval(UInterval x);
void testNewOr(UInterval a, UInterval b);
UInterval newor(UInterval a, UInterval b);

std::ostream& operator<<(std::ostream& os, const UInterval& x);

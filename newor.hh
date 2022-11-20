#include <iostream>  // std::cout
#include <string>    // std::string
#include <utility>   // std::pair, std::make_pair

typedef std::pair<unsigned int, unsigned int> UInterval;
typedef std::pair<int, int>                   SInterval;

bool empty(UInterval i);

// return the union of two intervals
UInterval operator+(const UInterval& a, const UInterval& b);

// msb: most significant bit
unsigned int msb32(unsigned int x);

bool canSplitInterval(UInterval x, UInterval& a, UInterval& b);
void testSplitInterval(UInterval x);
void testUnsignedOr(UInterval a, UInterval b);

UInterval unsignedOr(UInterval a, UInterval b);
SInterval signedOr(SInterval a, SInterval b);

SInterval U2SInterval(UInterval x);

std::ostream& operator<<(std::ostream& os, const UInterval& x);

std::ostream& operator<<(std::ostream& os, const SInterval& x);

void testS2U2S(SInterval a);

void testSignedOr(SInterval a, SInterval b);

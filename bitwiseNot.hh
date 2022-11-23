#include "Interval.hh"

// computes bitwise not on unsigned intervals by brute force
UInterval bfUnsignedNot(const UInterval& a);
UInterval smartUnsignedNot(const UInterval& a);

// computes bitwise not on unsigned intervals by brute force
SInterval bfSignedNot(const SInterval& a);
SInterval smartSignedNot(const SInterval& a);

void testUnsignedNot(unsigned int lo, unsigned int hi);
void testSignedNot(int lo, int hi);

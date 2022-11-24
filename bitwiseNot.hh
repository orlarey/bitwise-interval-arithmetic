#include "Intervals.hh"

// computes bitwise not on UNUMervals by brute force
UInterval bfUnsignedNot(const UInterval& a);
UInterval smartUnsignedNot(const UInterval& a);

// computes bitwise not on UNUMervals by brute force
SInterval bfSignedNot(const SInterval& a);
SInterval smartSignedNot(const SInterval& a);

void testUnsignedNot(UNUM lo, UNUM hi);
void testSignedNot(SNUM lo, SNUM hi);

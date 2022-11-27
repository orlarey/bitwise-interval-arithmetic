#include "Intervals.hh"

// computes bitwise not on UNUMervals by brute force
UInterval bfUnsignedAnd(const UInterval& a, const UInterval& b);
UInterval smartUnsignedAnd(const UInterval& a, const UInterval& b);

// computes bitwise not on UNUMervals by brute force
SInterval bfSignedAnd(const SInterval& a, const SInterval& b);
SInterval smartSignedAnd(const SInterval& a, const SInterval& b);

void testUnsignedAnd(UInterval a, UInterval b);
void testSignedAnd(SInterval a, SInterval b);

void testUnsignedAnd(UNUM lo1, UNUM hi1, UNUM lo2, UNUM hi2);
void testSignedAnd(SNUM lo1, SNUM hi1, SNUM lo2, SNUM hi2);

UNUM loOr2(UInterval a, UInterval b);
UNUM hiOr2(UInterval a, UInterval b);

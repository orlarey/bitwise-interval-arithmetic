#include "Intervals.hh"

// computes bitwise not on UNUMervals by brute force
UInterval bfUnsignedOr(const UInterval& a, const UInterval& b);
UInterval smartUnsignedOr(const UInterval& a, const UInterval& b);

// computes bitwise not on UNUMervals by brute force
SInterval bfSignedOr(const SInterval& a, const SInterval& b);
SInterval smartSignedOr(const SInterval& a, const SInterval& b);

void testUnsignedOr(UInterval a, UInterval b);
void testSignedOr(SInterval a, SInterval b);

void testUnsignedOr(UNUM lo1, UNUM hi1, UNUM lo2, UNUM hi2);
void testSignedOr(SNUM lo1, SNUM hi1, SNUM lo2, SNUM hi2);

UNUM loOr2(UInterval a, UInterval b);
UNUM hiOr2(UInterval a, UInterval b);

#include "Intervals.hh"

// computes bitwise not on UNUMervals by brute force
UInterval bfUnsignedXOr(const UInterval& a, const UInterval& b);
UInterval smartUnsignedXOr(const UInterval& a, const UInterval& b);

// computes bitwise not on UNUMervals by brute force
SInterval bfSignedXOr(const SInterval& a, const SInterval& b);
SInterval smartSignedXOr(const SInterval& a, const SInterval& b);

void testUnsignedXOr(UInterval a, UInterval b);
void testSignedXOr(SInterval a, SInterval b);

void testUnsignedXOr(UNUM lo1, UNUM hi1, UNUM lo2, UNUM hi2);
void testSignedXOr(SNUM lo1, SNUM hi1, SNUM lo2, SNUM hi2);

UNUM loOr2(UInterval a, UInterval b);
UNUM hiOr2(UInterval a, UInterval b);

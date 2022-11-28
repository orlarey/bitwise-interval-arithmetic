#include "Intervals.hh"

// computes bitwise not on UNUMervals by brute force
UInterval bfUnsignedOr(const UInterval& a, const UInterval& b);
UInterval smartUnsignedOr(const UInterval& a, const UInterval& b);

// computes bitwise not on UNUMervals by brute force
SInterval bfSignedOr(const SInterval& a, const SInterval& b);
SInterval smartSignedOr(const SInterval& a, const SInterval& b);

void testUnsignedOr(UInterval a, UInterval b);
void testSignedOr(SInterval a, SInterval b);

void testUnsignedOr(unsigned int lo1, unsigned int hi1, unsigned int lo2, unsigned int hi2);
void testSignedOr(int lo1, int hi1, int lo2, int hi2);

unsigned int loOr2(UInterval a, UInterval b);
unsigned int hiOr2(UInterval a, UInterval b);

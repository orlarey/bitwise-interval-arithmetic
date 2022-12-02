#include "bitwiseIntervals.hh"

// computes bitwise not on UNUMervals by brute force
UInterval bfUnsignedXOr(const UInterval& a, const UInterval& b);
UInterval bitwiseUnsignedXOr(const UInterval& a, const UInterval& b);

// computes bitwise not on UNUMervals by brute force
SInterval bfSignedXOr(const SInterval& a, const SInterval& b);
SInterval bitwiseSignedXOr(const SInterval& a, const SInterval& b);

void testUnsignedXOr(UInterval a, UInterval b);
void testSignedXOr(SInterval a, SInterval b);

void testUnsignedXOr(unsigned int lo1, unsigned int hi1, unsigned int lo2, unsigned int hi2);
void testSignedXOr(int lo1, int hi1, int lo2, int hi2);

unsigned int loOr2(UInterval a, UInterval b);
unsigned int hiOr2(UInterval a, UInterval b);

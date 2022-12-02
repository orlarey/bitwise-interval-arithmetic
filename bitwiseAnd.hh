#include "bitwiseOperations.hh"

namespace itv
{
// computes bitwise not on UNUMervals by brute force
UInterval bfUnsignedAnd(const UInterval& a, const UInterval& b);
UInterval bitwiseUnsignedAnd(const UInterval& a, const UInterval& b);

// computes bitwise not on UNUMervals by brute force
SInterval bfSignedAnd(const SInterval& a, const SInterval& b);
SInterval bitwiseSignedAnd(const SInterval& a, const SInterval& b);

void testUnsignedAnd(UInterval a, UInterval b);
void testSignedAnd(SInterval a, SInterval b);

void testUnsignedAnd(unsigned int lo1, unsigned int hi1, unsigned int lo2, unsigned int hi2);
void testSignedAnd(int lo1, int hi1, int lo2, int hi2);

unsigned int loOr2(UInterval a, UInterval b);
unsigned int hiOr2(UInterval a, UInterval b);
}
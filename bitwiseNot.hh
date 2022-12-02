#include "bitwiseIntervals.hh"
namespace itv
{
// computes bitwise not on UNUMervals by brute force
UInterval bfUnsignedNot(const UInterval& a);
UInterval bitwiseUnsignedNot(const UInterval& a);

// computes bitwise not on UNUMervals by brute force
SInterval bfSignedNot(const SInterval& a);
SInterval bitwiseSignedNot(const SInterval& a);

void testUnsignedNot(const UInterval& a);

void testSignedNot(const SInterval& a);
}  // namespace itv

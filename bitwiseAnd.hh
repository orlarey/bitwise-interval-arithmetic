#include "bitwiseOperations.hh"

namespace itv
{
// computes bitwise AND by brute force
UInterval bfUnsignedAnd(const UInterval& a, const UInterval& b);
SInterval bfSignedAnd(const SInterval& a, const SInterval& b);

bool testUnsignedAnd(UInterval a, UInterval b);
bool testSignedAnd(SInterval a, SInterval b);
}  // namespace itv
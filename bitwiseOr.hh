#include "bitwiseOperations.hh"

namespace itv
{
// computes bitwise not by brute force
UInterval bfUnsignedOr(const UInterval& a, const UInterval& b);
SInterval bfSignedOr(const SInterval& a, const SInterval& b);

bool testUnsignedOr(UInterval a, UInterval b);
bool testSignedOr(SInterval a, SInterval b);
}  // namespace itv

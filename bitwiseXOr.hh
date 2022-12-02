#include "bitwiseOperations.hh"

namespace itv
{
// computes bitwise XOR by brute force
UInterval bfUnsignedXOr(const UInterval& a, const UInterval& b);
SInterval bfSignedXOr(const SInterval& a, const SInterval& b);

bool testUnsignedXOr(UInterval a, UInterval b);
bool testSignedXOr(SInterval a, SInterval b);
}  // namespace itv

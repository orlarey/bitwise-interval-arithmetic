#include "bitwiseOperations.hh"
namespace itv
{
// computes bitwise NOT by brute force
UInterval bfUnsignedNot(const UInterval& a);
SInterval bfSignedNot(const SInterval& a);

bool testUnsignedNot(const UInterval& a);
bool testSignedNot(const SInterval& a);
}  // namespace itv

#include <limits>

#include "bitwiseOperations.hh"

namespace itv
{
// computes bitwise not on UNUMervals by brute force
UInterval bfUnsignedNot(const UInterval& a)
{
    // r is isEmpty by default
    UInterval r{std::numeric_limits<unsigned int>::max(), 0};

    for (unsigned int i = a.lo; i <= a.hi; ++i) {
        unsigned int ni = ~i;
        if (ni < r.lo) r.lo = ni;
        if (ni > r.hi) r.hi = ni;
    }
    return r;
}

// computes bitwise not on UNUMervals by brute force
SInterval bfSignedNot(const SInterval& a)
{
    // r is isEmpty by default
    SInterval r = SEMPTY;

    for (int i = a.lo; i <= a.hi; ++i) {
        int ni = ~i;
        if (ni < r.lo) r.lo = ni;
        if (ni > r.hi) r.hi = ni;
    }
    return r;
}

bool testUnsignedNot(const UInterval& a)
{
    UInterval r1 = bfUnsignedNot(a);
    UInterval r2 = bitwiseUnsignedNot(a);

    if (r1 != r2) {
        std::cout << "ERROR: " << a << " -> " << r1 << " != " << r2 << std::endl;
        return false;
    }
    return true;
}

bool testSignedNot(const SInterval& a)
{
    SInterval r1 = bfSignedNot(a);
    SInterval r2 = bitwiseSignedNot(a);
    if (r1 != r2) {
        std::cout << "ERROR: " << a << " -> " << r1 << " != " << r2 << std::endl;
        return false;
    }
    return true;
}
}  // namespace itv

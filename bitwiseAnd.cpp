#include <cassert>
#include <chrono>
#include <limits>
#include <tuple>
#include <unordered_map>

#include "bitwiseAnd.hh"
#include "bitwiseNot.hh"
#include "bitwiseOperations.hh"
#include "bitwiseOr.hh"

namespace itv
{

bool testUnsignedAnd(UInterval a, UInterval b)
{
    UInterval smart = bitwiseUnsignedAnd(a, b);
    UInterval bf    = bfUnsignedAnd(a, b);

    if (bf != smart) {
        std::cout << "ERROR: " << a << " & " << b << " = " << bf << " but got " << smart << std::endl;
        return false;
    }
    return true;
}

bool testSignedAnd(SInterval a, SInterval b)
{
    SInterval bf    = bfSignedAnd(a, b);
    SInterval smart = bitwiseSignedAnd(a, b);

    if (bf != smart) {
        std::cout << "ERROR: " << a << " & " << b << " = " << bf << " but got " << smart << std::endl;
        return false;
    }
    return true;
}

UInterval bfUnsignedAnd(const UInterval& a, const UInterval& b)
{
    if (isEmpty(a) || isEmpty(b)) return UEMPTY;
    UInterval result = UEMPTY;
    for (unsigned int i = a.lo; i <= a.hi; i++) {
        for (unsigned int j = b.lo; j <= b.hi; j++) {
            unsigned int r = i & j;
            if (r < result.lo) result.lo = (unsigned int)(r);
            if (r > result.hi) result.hi = (unsigned int)(r);
        }
    }
    return result;
}

SInterval bfSignedAnd(const SInterval& a, const SInterval& b)
{
    if (isEmpty(a) || isEmpty(b)) return SEMPTY;
    SInterval result = SEMPTY;
    for (int i = a.lo; i <= a.hi; i++) {
        for (int j = b.lo; j <= b.hi; j++) {
            int r = i & j;
            if (r < result.lo) result.lo = (int)(r);
            if (r > result.hi) result.hi = (int)(r);
        }
    }
    return result;
}
}  // namespace itv

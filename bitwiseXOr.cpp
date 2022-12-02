#include <cassert>
#include <chrono>
#include <limits>
#include <tuple>
#include <unordered_map>

#include "bitwiseAnd.hh"
#include "bitwiseNot.hh"
#include "bitwiseOperations.hh"
#include "bitwiseOr.hh"
#include "bitwiseXOr.hh"

namespace itv
{

bool testUnsignedXOr(UInterval a, UInterval b)
{
    UInterval smart = bitwiseUnsignedXOr(a, b);
    UInterval bf    = bfUnsignedXOr(a, b);
    if (bf != smart) {
        std::cout << "ERROR: " << a << " ^ " << b << " = " << bf << " but got " << smart << std::endl;
        return false;
    }
    return true;
}

bool testSignedXOr(SInterval a, SInterval b)
{
    SInterval bf    = bfSignedXOr(a, b);
    SInterval smart = bitwiseSignedXOr(a, b);
    if (bf != smart) {
        std::cout << "ERROR: " << a << " ^ " << b << " = " << bf << " but we got " << smart << std::endl;
        return false;
    }
    return true;
}

UInterval bfUnsignedXOr(const UInterval& a, const UInterval& b)
{
    if (isEmpty(a) || isEmpty(b)) return UEMPTY;
    UInterval result = UEMPTY;
    for (unsigned int i = a.lo; i <= a.hi; i++) {
        for (unsigned int j = b.lo; j <= b.hi; j++) {
            unsigned int r = i ^ j;
            if (r < result.lo) result.lo = (unsigned int)(r);
            if (r > result.hi) result.hi = (unsigned int)(r);
        }
    }
    return result;
}

SInterval bfSignedXOr(const SInterval& a, const SInterval& b)
{
    if (isEmpty(a) || isEmpty(b)) return SEMPTY;
    SInterval result = SEMPTY;
    for (int i = a.lo; i <= a.hi; i++) {
        for (int j = b.lo; j <= b.hi; j++) {
            int r = i ^ j;
            if (r < result.lo) result.lo = (int)(r);
            if (r > result.hi) result.hi = (int)(r);
        }
    }
    return result;
}
}  // namespace itv

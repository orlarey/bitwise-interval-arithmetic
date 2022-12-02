#include <cassert>
#include <chrono>
#include <limits>
#include <tuple>
#include <unordered_map>

#include "Intervals.hh"
#include "bitwiseAnd.hh"
#include "bitwiseNot.hh"
#include "bitwiseOr.hh"

#include "bitwiseXOr.hh"

void testUnsignedXOr(unsigned int lo1, unsigned int hi1, unsigned int lo2, unsigned int hi2)
{
    UInterval a{lo1, hi1};
    UInterval b{lo2, hi2};
    testUnsignedXOr(a, b);
}

void testUnsignedXOr(UInterval a, UInterval b)
{
    UInterval smart = bitwiseUnsignedXOr(a, b);
    UInterval bf    = bfUnsignedXOr(a, b);
    if (bf == smart) {
        // std::cout << "OK: " << a << " ^ " << b << " = " << bf << std::endl;
    } else {
        std::cout << "ERROR: " << a << " ^ " << b << " = " << bf << " but got " << smart << std::endl;
    }
}

void testSignedXOr(int lo1, int hi1, int lo2, int hi2)
{
    SInterval a{lo1, hi1};
    SInterval b{lo2, hi2};
    testSignedXOr(a, b);
}

void testSignedXOr(SInterval a, SInterval b)
{
    SInterval bf    = bfSignedXOr(a, b);
    SInterval smart = bitwiseSignedXOr(a, b);
    if (bf == smart) {
        // std::cout << "OK: " << a << " ^ " << b << " = " << bf << std::endl;
    } else {
        std::cout << "ERROR: " << a << " ^ " << b << " = " << bf << " but we got " << smart << std::endl;
    }
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

//==============================================================================
// main algorithm
// p^q = p|q & non(p&q)
//

// p&q = non(non(p)|non(q))

UInterval bitwiseUnsignedXOr(const UInterval& a, const UInterval& b)
{
    return bitwiseUnsignedAnd(bitwiseUnsignedOr(a, b), bitwiseUnsignedNot(bitwiseUnsignedAnd(a, b)));
}

SInterval bitwiseSignedXOr(const SInterval& a, const SInterval& b)
{
    auto [an, ap] = signSplit(a);
    auto [bn, bp] = signSplit(b);
    UInterval pp  = bitwiseUnsignedXOr(ap, bp);
    UInterval nn  = bitwiseUnsignedXOr(an, bn);
    UInterval pn  = bitwiseUnsignedXOr(ap, bn);
    UInterval np  = bitwiseUnsignedXOr(an, bp);
    return signMerge(np + pn, pp + nn);
}

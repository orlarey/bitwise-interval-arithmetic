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
    UInterval smart = smartUnsignedXOr(a, b);
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
    SInterval smart = smartSignedXOr(a, b);
    if (bf == smart) {
        // std::cout << "OK: " << a << " ^ " << b << " = " << bf << std::endl;
    } else {
        std::cout << "ERROR: " << a << " ^ " << b << " = " << bf << " but we got " << smart << std::endl;
    }
}

UInterval bfUnsignedXOr(const UInterval& a, const UInterval& b)
{
    if (empty(a) || empty(b)) return UEmpty();
    UInterval result = UEmpty();
    for (unsigned int i = a.first; i <= a.second; i++) {
        for (unsigned int j = b.first; j <= b.second; j++) {
            unsigned int r = i ^ j;
            if (r < result.first) result.first = (unsigned int)(r);
            if (r > result.second) result.second = (unsigned int)(r);
        }
    }
    return result;
}

SInterval bfSignedXOr(const SInterval& a, const SInterval& b)
{
    if (empty(a) || empty(b)) return SEmpty();
    SInterval result = SEmpty();
    for (int i = a.first; i <= a.second; i++) {
        for (int j = b.first; j <= b.second; j++) {
            int r = i ^ j;
            if (r < result.first) result.first = (int)(r);
            if (r > result.second) result.second = (int)(r);
        }
    }
    return result;
}

//==============================================================================
// main algorithm
// p^q = p|q & non(p&q)
//

// p&q = non(non(p)|non(q))

UInterval smartUnsignedXOr(const UInterval& a, const UInterval& b)
{
    return smartUnsignedAnd(smartUnsignedOr(a, b), smartUnsignedNot(smartUnsignedAnd(a, b)));
}

SInterval smartSignedXOr(const SInterval& a, const SInterval& b)
{
    auto [an, ap] = signSplit(a);
    auto [bn, bp] = signSplit(b);
    UInterval pp  = smartUnsignedXOr(ap, bp);
    UInterval nn  = smartUnsignedXOr(an, bn);
    UInterval pn  = smartUnsignedXOr(ap, bn);
    UInterval np  = smartUnsignedXOr(an, bp);
    return signMerge(np + pn, pp + nn);
}

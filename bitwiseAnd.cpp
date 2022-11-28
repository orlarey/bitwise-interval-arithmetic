#include <cassert>
#include <chrono>
#include <limits>
#include <tuple>
#include <unordered_map>

#include "Intervals.hh"
#include "bitwiseAnd.hh"
#include "bitwiseNot.hh"
#include "bitwiseOr.hh"

void testUnsignedAnd(unsigned int lo1, unsigned int hi1, unsigned int lo2, unsigned int hi2)
{
    UInterval a{lo1, hi1};
    UInterval b{lo2, hi2};
    testUnsignedAnd(a, b);
}

void testUnsignedAnd(UInterval a, UInterval b)
{
    UInterval smart = smartUnsignedAnd(a, b);
    UInterval bf    = bfUnsignedAnd(a, b);
    if (bf == smart) {
        // std::cout << "OK: " << a << " & " << b << " = " << bf << std::endl;
    } else {
        std::cout << "ERROR: " << a << " & " << b << " = " << bf << " but got " << smart << std::endl;
    }
}

void testSignedAnd(int lo1, int hi1, int lo2, int hi2)
{
    SInterval a{lo1, hi1};
    SInterval b{lo2, hi2};
    testSignedAnd(a, b);
}

void testSignedAnd(SInterval a, SInterval b)
{
    SInterval bf    = bfSignedAnd(a, b);
    SInterval smart = smartSignedAnd(a, b);
    if (bf == smart) {
        // std::cout << "OK: " << a << " & " << b << " = " << bf << std::endl;
    } else {
        std::cout << "ERROR: " << a << " & " << b << " = " << bf << " but we got " << smart << std::endl;
    }
}

UInterval bfUnsignedAnd(const UInterval& a, const UInterval& b)
{
    if (empty(a) || empty(b)) return UEmpty();
    UInterval result = UEmpty();
    for (unsigned int i = a.first; i <= a.second; i++) {
        for (unsigned int j = b.first; j <= b.second; j++) {
            unsigned int r = i & j;
            if (r < result.first) result.first = (unsigned int)(r);
            if (r > result.second) result.second = (unsigned int)(r);
        }
    }
    return result;
}

SInterval bfSignedAnd(const SInterval& a, const SInterval& b)
{
    if (empty(a) || empty(b)) return SEmpty();
    SInterval result = SEmpty();
    for (int i = a.first; i <= a.second; i++) {
        for (int j = b.first; j <= b.second; j++) {
            int r = i & j;
            if (r < result.first) result.first = (int)(r);
            if (r > result.second) result.second = (int)(r);
        }
    }
    return result;
}

//==============================================================================
// main algorithm

UInterval smartUnsignedAnd(const UInterval& a, const UInterval& b)
{
    return smartUnsignedNot(smartUnsignedOr(smartUnsignedNot(a), smartUnsignedNot(b)));
}

SInterval smartSignedAnd(const SInterval& a, const SInterval& b)
{
    return smartSignedNot(smartSignedOr(smartSignedNot(a), smartSignedNot(b)));
}

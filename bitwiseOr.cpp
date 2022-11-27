#include <cassert>
#include <chrono>
#include <limits>
#include <tuple>
#include <unordered_map>

#include "Intervals.hh"
#include "bitwiseOr.hh"

void testUnsignedOr(UNUM lo1, UNUM hi1, UNUM lo2, UNUM hi2)
{
    UInterval a{lo1, hi1};
    UInterval b{lo2, hi2};
    testUnsignedOr(a, b);
}

void testUnsignedOr(UInterval a, UInterval b)
{
    UInterval smart = smartUnsignedOr(a, b);
    UInterval bf    = bfUnsignedOr(a, b);

    if (bf == smart) {
        // std::cout << "OK: " << a << " | " << b << " = " << bf << std::endl;
    } else {
        std::cout << "ERROR: " << a << " | " << b << " = " << bf << " but got " << smart << std::endl;
    }
}

void testSignedOr(SNUM lo1, SNUM hi1, SNUM lo2, SNUM hi2)
{
    SInterval a{lo1, hi1};
    SInterval b{lo2, hi2};
    testSignedOr(a, b);
}

void testSignedOr(SInterval a, SInterval b)
{
    SInterval bf    = bfSignedOr(a, b);
    SInterval smart = smartSignedOr(a, b);
    if (bf == smart) {
        // std::cout << "OK: " << a << " | " << b << " = " << bf << std::endl;
    } else {
        std::cout << "ERROR: " << a << " | " << b << " = " << bf << " but we got " << smart << std::endl;
    }
}

UInterval bfUnsignedOr(const UInterval& a, const UInterval& b)
{
    if (empty(a) || empty(b)) return UEmpty();
    UInterval result = UEmpty();
    for (unsigned int i = a.first; i <= a.second; i++) {
        for (unsigned int j = b.first; j <= b.second; j++) {
            unsigned int r = i | j;
            if (r < result.first) result.first = unum(r);
            if (r > result.second) result.second = unum(r);
        }
    }
    return result;
}

SInterval bfSignedOr(const SInterval& a, const SInterval& b)
{
    if (empty(a) || empty(b)) return SEmpty();
    SInterval result = SEmpty();
    for (int i = a.first; i <= a.second; i++) {
        for (int j = b.first; j <= b.second; j++) {
            int r = i | j;
            if (r < result.first) result.first = snum(r);
            if (r > result.second) result.second = snum(r);
        }
    }
    return result;
}

//==============================================================================
// main algorithm
UInterval operator+(const UInterval& a, UNUM offset);
UInterval operator-(const UInterval& a, UNUM offset);
UNUM      loOr2(UInterval a, UInterval b);
UNUM      hiOr2(UInterval a, UInterval b);

// split interval according to its msb
std::tuple<UNUM, UInterval, UInterval> splitInterval(UInterval x);

UInterval smartUnsignedOr(const UInterval& a, const UInterval& b)
{
    if (a == UInterval{0, 0}) return b;
    if (b == UInterval{0, 0}) return a;
    if (empty(a)) return a;
    if (empty(b)) return b;
    UInterval r{loOr2(a, b), hiOr2(a, b)};
    return r;
}

//==============================================================================
static bool contains(const UInterval& i, UNUM x)
{
    return (i.first <= x) && (x <= i.second);
}

UNUM hiOr2(UInterval a, UInterval b)
{
    // simple cases
    if (a.first == 0 && a.second == 0) return b.second;
    if (b.first == 0 && b.second == 0) return a.second;
    // analyze and split the intervals
    auto [ma, a0, a1] = splitInterval(a);
    auto [mb, b0, b1] = splitInterval(b);
    if (mb > ma) {
        if (contains(a, mb - 1)) return 2 * mb - 1;
        return hiOr2(b1 - mb, a) + mb;
    }
    if (ma > mb) {
        if (contains(b, ma - 1)) return 2 * ma - 1;
        return hiOr2(a1 - ma, b) + ma;
    }
    // ma == mb != 0
    if (empty(a0) && empty(b0)) return hiOr2(a1 - ma, b1 - ma) + ma;
    if (empty(a0)) return std::max(hiOr2(a1 - ma, b1 - ma), hiOr2(a1 - ma, b0)) + ma;
    if (empty(b0)) return std::max(hiOr2(a1 - ma, b1 - ma), hiOr2(a0, b1 - ma)) + ma;
    return std::max(hiOr2(a1 - ma, b1 - ma), std::max(hiOr2(a1 - ma, b0), hiOr2(a0, b1 - ma))) + ma;
}

UNUM loOr2(UInterval a, UInterval b)
{
    // empty case
    if (empty(a) || empty(b)) return 0;

    // zero cases
    if (a.first == 0) return b.first;
    if (b.first == 0) return a.first;

    // non zero cases
    auto [ma, a0, a1] = splitInterval(a);
    auto [mb, b0, b1] = splitInterval(b);
    assert(ma != 0 && mb != 0);

    // obvious cases
    if (ma > mb) {
        if (empty(a0)) return loOr2(a1 - ma, b) | ma;  // ma bit unavoidable !
        return loOr2(a0, b);
    }
    if (mb > ma) {
        if (empty(b0)) return loOr2(a, b1 - mb) | mb;
        return loOr2(a, b0);
    }
    // ma == mb != 0
    if (!empty(a0) && !empty(b0)) return loOr2(a0, b0);               // obvious case !
    if (empty(a0) && empty(b0)) return loOr2(a1 - ma, b1 - ma) | ma;  // ma bit unavoidable !
    if (empty(a0)) return std::min(loOr2(a1 - ma, b0) | ma, loOr2(a1 - ma, b1 - ma) | ma);
    return std::min(loOr2(a0, b1 - mb) | mb, loOr2(a1 - ma, b1 - ma) | ma);
}

//==============================================================================
// details

UInterval operator+(const UInterval& a, UNUM offset)
{
    return {(UNUM)(a.first + offset), (UNUM)(a.second + offset)};
}

UInterval operator-(const UInterval& a, UNUM offset)
{
    return {(UNUM)(a.first - offset), (UNUM)(a.second - offset)};
}

UNUM msb32(UNUM x)
{
    x |= (x >> 1);
    x |= (x >> 2);
    x |= (x >> 4);
    x |= (x >> 8);
    x |= (x >> 16);
    return (x & ~(x >> 1));
}

// split interval according to its msb
std::tuple<UNUM, UInterval, UInterval> splitInterval(UInterval x)
{
    if (x.first == 0 && x.second == 0) return {0, {1, 0}, x};  // special case, no msb
    UNUM m = msb32(x.second);
    assert(m > 0);

    if (m <= x.first) return {m, {1, 0}, x};  // no msb in the interval
    return {m, {x.first, (UNUM)(m - 1)}, {m, x.second}};
}

SInterval smartSignedOr(const SInterval& a, const SInterval& b)
{
    auto [an, ap] = signSplit(a);
    auto [bn, bp] = signSplit(b);
    UInterval pp  = smartUnsignedOr(ap, bp);
    UInterval nn  = smartUnsignedOr(an, bn);
    UInterval pn  = smartUnsignedOr(ap, bn);
    UInterval np  = smartUnsignedOr(an, bp);
    return signMerge(np + nn + pn, pp);
}

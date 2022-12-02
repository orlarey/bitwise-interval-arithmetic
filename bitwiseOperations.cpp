#include <cassert>

#include "Intervals.hh"
#include "bitwiseOperations.hh"

UInterval bitwiseUnsignedNot(const UInterval& a)
{
    return UInterval{(unsigned int)(~a.hi), (unsigned int)(~a.lo)};
}

SInterval bitwiseSignedNot(const SInterval& a)
{
    return SInterval{(int)(~a.hi), (int)(~a.lo)};
}

//==============================================================================
// main algorithm
UInterval    operator+(const UInterval& a, unsigned int offset);
UInterval    operator-(const UInterval& a, unsigned int offset);
unsigned int loOr2(UInterval a, UInterval b);
unsigned int hiOr2(UInterval a, UInterval b);

// split interval according to its msb
std::tuple<unsigned int, UInterval, UInterval> splitInterval(UInterval x);

UInterval bitwiseUnsignedOr(const UInterval& a, const UInterval& b)
{
    if (a == UInterval{0, 0}) return b;
    if (b == UInterval{0, 0}) return a;
    if (isEmpty(a)) return a;
    if (isEmpty(b)) return b;
    UInterval r{loOr2(a, b), hiOr2(a, b)};
    return r;
}

//==============================================================================
static bool contains(const UInterval& i, unsigned int x)
{
    return (i.lo <= x) && (x <= i.hi);
}

unsigned int hiOr2(UInterval a, UInterval b)
{
    // simple cases
    if (a.lo == 0 && a.hi == 0) return b.hi;
    if (b.lo == 0 && b.hi == 0) return a.hi;
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
    if (isEmpty(a0) && isEmpty(b0)) return hiOr2(a1 - ma, b1 - ma) + ma;
    if (isEmpty(a0)) return std::max(hiOr2(a1 - ma, b1 - ma), hiOr2(a1 - ma, b0)) + ma;
    if (isEmpty(b0)) return std::max(hiOr2(a1 - ma, b1 - ma), hiOr2(a0, b1 - ma)) + ma;
    return std::max(hiOr2(a1 - ma, b1 - ma), std::max(hiOr2(a1 - ma, b0), hiOr2(a0, b1 - ma))) + ma;
}

unsigned int loOr2(UInterval a, UInterval b)
{
    // isEmpty case
    if (isEmpty(a) || isEmpty(b)) return 0;

    // zero cases
    if (a.lo == 0) return b.lo;
    if (b.lo == 0) return a.lo;

    // non zero cases
    auto [ma, a0, a1] = splitInterval(a);
    auto [mb, b0, b1] = splitInterval(b);
    assert(ma != 0 && mb != 0);

    // obvious cases
    if (ma > mb) {
        if (isEmpty(a0)) return loOr2(a1 - ma, b) | ma;  // ma bit unavoidable !
        return loOr2(a0, b);
    }
    if (mb > ma) {
        if (isEmpty(b0)) return loOr2(a, b1 - mb) | mb;
        return loOr2(a, b0);
    }
    // ma == mb != 0
    if (!isEmpty(a0) && !isEmpty(b0)) return loOr2(a0, b0);               // obvious case !
    if (isEmpty(a0) && isEmpty(b0)) return loOr2(a1 - ma, b1 - ma) | ma;  // ma bit unavoidable !
    if (isEmpty(a0)) return std::min(loOr2(a1 - ma, b0) | ma, loOr2(a1 - ma, b1 - ma) | ma);
    return std::min(loOr2(a0, b1 - mb) | mb, loOr2(a1 - ma, b1 - ma) | ma);
}

//==============================================================================
// details

UInterval operator+(const UInterval& a, unsigned int offset)
{
    return {(unsigned int)(a.lo + offset), (unsigned int)(a.hi + offset)};
}

UInterval operator-(const UInterval& a, unsigned int offset)
{
    return {(unsigned int)(a.lo - offset), (unsigned int)(a.hi - offset)};
}

unsigned int msb32(unsigned int x)
{
    x |= (x >> 1);
    x |= (x >> 2);
    x |= (x >> 4);
    x |= (x >> 8);
    x |= (x >> 16);
    return (x & ~(x >> 1));
}

// split interval according to its msb
std::tuple<unsigned int, UInterval, UInterval> splitInterval(UInterval x)
{
    if (x.lo == 0 && x.hi == 0) return {0, {1, 0}, x};  // special case, no msb
    unsigned int m = msb32(x.hi);
    assert(m > 0);

    if (m <= x.lo) return {m, {1, 0}, x};  // no msb in the interval
    return {m, {x.lo, (unsigned int)(m - 1)}, {m, x.hi}};
}

SInterval bitwiseSignedOr(const SInterval& a, const SInterval& b)
{
    auto [an, ap] = signSplit(a);
    auto [bn, bp] = signSplit(b);
    UInterval pp  = bitwiseUnsignedOr(ap, bp);
    UInterval nn  = bitwiseUnsignedOr(an, bn);
    UInterval pn  = bitwiseUnsignedOr(ap, bn);
    UInterval np  = bitwiseUnsignedOr(an, bp);
    return signMerge(np + nn + pn, pp);
}

//==============================================================================
// main algorithm

UInterval bitwiseUnsignedAnd(const UInterval& a, const UInterval& b)
{
    return bitwiseUnsignedNot(bitwiseUnsignedOr(bitwiseUnsignedNot(a), bitwiseUnsignedNot(b)));
}

SInterval bitwiseSignedAnd(const SInterval& a, const SInterval& b)
{
    return bitwiseSignedNot(bitwiseSignedOr(bitwiseSignedNot(a), bitwiseSignedNot(b)));
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

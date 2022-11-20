#include "newor.hh"
#include <tuple>

bool empty(UInterval i)
{
    return i.first > i.second;
}

UInterval operator+(const UInterval& a, unsigned int offset)
{
    return {a.first + offset, a.second + offset};
}

UInterval operator-(const UInterval& a, unsigned int offset)
{
    return {a.first - offset, a.second - offset};
}

// union of signed intervals
SInterval reunion(const SInterval& a, const SInterval& b)
{
    return {std::min(a.first, b.first), std::max(a.second, b.second)};
}

// union of intervals
UInterval reunion(const UInterval& a, const UInterval& b)
{
    return {std::min(a.first, b.first), std::max(a.second, b.second)};
}

UInterval reunion(const UInterval& a, const UInterval& b, const UInterval& c)
{
    return reunion(a, reunion(b, c));
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

bool canSplitInterval(UInterval x, UInterval& a, UInterval& b)
{
    unsigned int m0 = msb32(x.first);
    unsigned int m1 = msb32(x.second);
    // std::cout << "canSplitInterval: " << x << " m0 = " << m0 << " m1 = " << m1 << std::endl;
    if (m0 == m1) {
        return false;
    }
    a = {x.first, m1 - 1};
    b = {m1, x.second};
    return true;
}

/**
 * @brief trim : msb part
 *
 * @param x
 * @return UInterval
 */
UInterval trim(UInterval x)
{
    UInterval x0, x1;
    if (canSplitInterval(x, x0, x1)) return x1;
    return x;
}

std::ostream& operator<<(std::ostream& os, const UInterval& x)
{
    os << x.first << ".." << x.second;
    return os;
}

std::ostream& operator<<(std::ostream& os, const SInterval& x)
{
    os << x.first << ".." << x.second;
    return os;
}

void testSplitInterval(UInterval a)
{
    UInterval b(0, 0);
    UInterval c(0, 0);

    if (canSplitInterval(a, b, c)) {
        std::cout << "can split " << a << " into " << b << " and " << c << std::endl;
    } else {
        std::cout << "cannot split " << a << std::endl;
    }
}

unsigned int hiOr(UInterval a, UInterval b)
{
    auto ma = msb32(a.second);
    auto mb = msb32(b.second);
    if (ma == 0) return b.second;
    if (mb == 0) return a.second;
    if (mb > ma) return hiOr(trim(b) - mb, a) + mb;
    if (ma > mb) return hiOr(trim(a) - ma, b) + ma;
    // ma == mb
    UInterval a0, a1, b0, b1;
    if (canSplitInterval(a, a0, a1)) {
        if (canSplitInterval(b, b0, b1)) {
            return std::max(hiOr(a1 - ma, b1 - ma), std::max(hiOr(a1 - ma, b0), hiOr(a0, b1 - ma))) + ma;
        }
        return std::max(hiOr(a1 - ma, b - ma), hiOr(a0, b - ma)) + ma;
    }
    if (canSplitInterval(b, b0, b1)) {
        return std::max(hiOr(a - ma, b1 - ma), hiOr(a - ma, b0)) + ma;
    }
    return hiOr(a - ma, b - ma) + ma;
}

unsigned int loOr(UInterval a, UInterval b)
{
    auto ma = msb32(a.second);
    auto mb = msb32(b.second);
    if (ma == 0) return b.first;
    if (mb == 0) return a.first;

    UInterval a0, a1, b0, b1;

    if (ma > mb) {
        if (canSplitInterval(a, a0, a1)) return loOr(a0, b);
        return loOr(a - ma, b) + ma;
    }

    if (mb > ma) {
        if (canSplitInterval(b, b0, b1)) return loOr(b0, a);
        return loOr(b - mb, a) + mb;
    }

    // ma == mb
    if (canSplitInterval(a, a0, a1)) {
        if (canSplitInterval(b, b0, b1)) {
            return loOr(a0, b0);
        }
        // ma is necessarely part of the result
        return std::min(loOr(a0, b - ma), loOr(a1 - ma, b - ma)) + ma;
    }
    if (canSplitInterval(b, b0, b1)) {
        return std::min(loOr(a - ma, b1 - ma), loOr(a - ma, b0)) + ma;
    }
    return loOr(a - ma, b - ma) + ma;
}

UInterval unsignedOr(UInterval a, UInterval b)
{
    if (empty(a)) return a;
    if (empty(b)) return b;
    return {loOr(a, b), hiOr(a, b)};
}

void testUnsignedOr(UInterval a, UInterval b)
{
    std::cout << "newor  (" << a << ", " << b << ") = " << unsignedOr(a, b) << std::endl;
}

//==================================
//
// signd OR
//
//=====================================

std::pair<UInterval, UInterval> signSplit(SInterval a)
{
    if (a.first >= 0) return {{1, 0}, {a.first, a.second}};
    if (a.second < 0) return {{a.first, a.second}, {1, 0}};
    return {{a.first, -1}, {0, a.second}};
}

SInterval U2SInterval(UInterval a)
{
    if ((a.first > INT32_MAX) || (a.second <= INT32_MAX)) {
        return {int(a.first), int(a.second)};
    }
    return {INT32_MIN, INT32_MAX};
}

SInterval S2U2S(SInterval a)
{
    auto [an, ap] = signSplit(a);
    if (empty(an)) return U2SInterval(ap);
    if (empty(ap)) return U2SInterval(an);
    return reunion(U2SInterval(ap), U2SInterval(an));
}

void testS2U2S(SInterval a)
{
    std::cout << "a = " << a.first << ".." << a.second << std::endl;
    SInterval b = S2U2S(a);
    if (a == b) {
        std::cout << "OK    : S2U2S(" << a << ") == " << b << std::endl;
    } else {
        std::cout << "WRONG : S2U2S(" << a << ") == " << b << std::endl;
    }
}

SInterval signedOr(SInterval a, SInterval b)
{
    auto [an, ap] = signSplit(a);
    auto [bn, bp] = signSplit(b);

    UInterval pp = unsignedOr(ap, bp);
    UInterval nn = unsignedOr(an, bn);
    UInterval pn = unsignedOr(ap, bn);
    UInterval np = unsignedOr(an, bp);

    SInterval s1 = U2SInterval(pp);
    SInterval s2 = U2SInterval(nn);
    SInterval s3 = U2SInterval(pn);
    SInterval s4 = U2SInterval(np);

    return reunion(reunion(s1, s2), reunion(s3, s4));
}

void testSignedOr(SInterval a, SInterval b)
{
    std::cout << "signedor  (" << a << ", " << b << ") = " << signedOr(a, b) << std::endl;
}

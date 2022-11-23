
#include "newor.hh"
#include "Interval.hh"

UInterval operator+(const UInterval& a, unsigned int offset)
{
    return {a.first + offset, a.second + offset};
}

UInterval operator-(const UInterval& a, unsigned int offset)
{
    return {a.first - offset, a.second - offset};
}

UInterval reunion(const UInterval& a, const UInterval& b, const UInterval& c)
{
    return a + b + c;
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
    return U2SInterval(ap) + U2SInterval(an);
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

    // std::cout << "s1 = " << s1 << std::endl;
    // std::cout << "s2 = " << s2 << std::endl;
    // std::cout << "s3 = " << s3 << std::endl;
    // std::cout << "s4 = " << s4 << std::endl;

    SInterval r1 = s1 + s2;
    // std::cout << "r1 = " << r1 << std::endl;

    SInterval r2 = s3 + s4;
    // std::cout << "r2 = " << r2 << std::endl;

    SInterval rr = r1 + r2;
    // std::cout << "rr = " << rr << std::endl;

    return rr;
}

void bruteforceOR(int lox, int hix, int loy, int hiy)
{
    // Value of INT_MAX is + 2147483647. Value of INT_MIN is - 2147483648.
    int loz = 2147483647;
    int hiz = -2147483648;
    for (int x = lox; x <= hix; x++) {
        for (int y = loy; y <= hiy; y++) {
            int z = x | y;
            if (z > hiz) hiz = z;
            if (z < loz) loz = z;
        }
    }
    std::cout << "BruteforceOr (" << lox << ".." << hix << ", " << loy << ".." << hiy << ") -> " << loz << ".." << hiz
              << std::endl;
}

void testSignedOr(SInterval a, SInterval b)
{
    bruteforceOR(a.first, a.second, b.first, b.second);
    SInterval c = signedOr(a, b);
    std::cout << "smartSignedOr(" << a << ", " << b << ") = " << c << std::endl;
}

#include "newor.hh"

UInterval operator+(const UInterval& a, unsigned int offset)
{
    return {a.first + offset, a.second + offset};
}

UInterval operator-(const UInterval& a, unsigned int offset)
{
    return {a.first - offset, a.second - offset};
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
    //std::cout << "canSplitInterval: " << x << " m0 = " << m0 << " m1 = " << m1 << std::endl;
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
    os  << x.first << ".." << x.second;
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

UInterval newor(UInterval a, UInterval b)
{
    return {loOr(a, b), hiOr(a, b)};
}

void testNewOr(UInterval a, UInterval b)
{
    std::cout << "newor  (" << a << ", " << b << ") = " << newor(a, b) << std::endl;
}

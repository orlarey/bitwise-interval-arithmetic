#include "newor.hh"

Interval operator+(const Interval& a, unsigned int offset)
{
    return {a.first + offset, a.second + offset};
}

Interval operator-(const Interval& a, unsigned int offset)
{
    return {a.first - offset, a.second - offset};
}

// union of intervals
Interval reunion(const Interval& a, const Interval& b)
{
    return {std::min(a.first, b.first), std::max(a.second, b.second)};
}

Interval reunion(const Interval& a, const Interval& b, const Interval& c)
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

bool canSplitInterval(Interval x, Interval& a, Interval& b)
{
    unsigned int m0 = msb32(x.first);
    unsigned int m1 = msb32(x.second);
    std::cout << "canSplitInterval: " << x << " m0 = " << m0 << " m1 = " << m1 << std::endl;
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
 * @return Interval
 */
Interval trim(Interval x)
{
    Interval x0, x1;
    if (canSplitInterval(x, x0, x1)) return x1;
    return x;
}

std::ostream& operator<<(std::ostream& os, const Interval& x)
{
    os << '[' << x.first << ',' << x.second << ']';
    return os;
}

void testSplitInterval(Interval a)
{
    Interval b(0, 0);
    Interval c(0, 0);

    if (canSplitInterval(a, b, c)) {
        std::cout << "can split " << a << " into " << b << " and " << c << std::endl;
    } else {
        std::cout << "cannot split " << a << std::endl;
    }
}

Interval newor(Interval a, Interval b)
{
    auto ma = msb32(a.second);
    auto mb = msb32(b.second);
    if (ma == 0) return b;
    if (mb == 0) return a;
    if (mb > ma) return newor(trim(b) - mb, a) + mb;
    if (ma > mb) return newor(trim(a) - ma, b) + ma;
    // ma == mb
    Interval a0, a1, b0, b1;
    if (canSplitInterval(a, a0, a1)) {
        if (canSplitInterval(b, b0, b1)) {
            return reunion(newor(a1 - ma, b1 - ma), newor(a1 - ma, b0), newor(a0, b1 - ma)) + ma;
        }
        return reunion(newor(a1 - ma, b - ma), newor(a0, b - ma)) + ma;
    }
    if (canSplitInterval(b, b0, b1)) {
        return reunion(newor(a - ma, b1 - ma), newor(a - ma, b0)) + ma;
    }
    return newor(a - ma, b - ma) + ma;
}

void testNewOr(Interval a, Interval b)
{
    std::cout << "newor(" << a << ", " << b << ") = " << newor(a, b) << std::endl;
}
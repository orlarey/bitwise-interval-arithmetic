#include <cassert>
#include <chrono>
#include <limits>
#include <tuple>
#include <unordered_map>

#include "bitwiseOr.hh"

void testUnsignedOr(unsigned int lo1, unsigned int hi1, unsigned int lo2, unsigned int hi2)
{
    using std::chrono::duration;
    using std::chrono::duration_cast;
    using std::chrono::high_resolution_clock;
    using std::chrono::milliseconds;

    UInterval a{lo1, hi1};
    UInterval b{lo2, hi2};
    auto      t1    = high_resolution_clock::now();
    UInterval bf    = bfUnsignedOr(a, b);
    auto      t2    = high_resolution_clock::now();
    auto      t3    = high_resolution_clock::now();
    UInterval smart = smartUnsignedOr(a, b);
    auto      t4    = high_resolution_clock::now();

    if (bf == smart) {
        std::cout << "OK: " << a << " | " << b << " = " << bf << std::endl;
        std::cout << "bf: " << duration_cast<milliseconds>(t2 - t1).count() << "ms" << std::endl;
        std::cout << "sm: " << duration_cast<milliseconds>(t4 - t3).count() << "ms" << std::endl;
    } else {
        std::cout << "ERROR: " << a << " | " << b << " = " << bf << " != " << smart << std::endl;
    }
}

void testSignedOr(int lo1, int hi1, int lo2, int hi2)
{
    SInterval a{lo1, hi1};
    SInterval b{lo2, hi2};
    SInterval bf    = bfSignedOr(a, b);
    SInterval smart = smartSignedOr(a, b);
    if (bf == smart) {
        std::cout << "OK: " << a << " | " << b << " = " << bf << std::endl;
    } else {
        std::cout << "ERROR: " << a << " | " << b << " = " << bf << " != " << smart << std::endl;
    }
}

UInterval bfUnsignedOr(const UInterval& a, const UInterval& b)
{
    UInterval result{std::numeric_limits<unsigned int>::max(), 0};
    for (unsigned int i = a.first; i <= a.second; i++) {
        for (unsigned int j = b.first; j <= b.second; j++) {
            unsigned int r = i | j;
            if (r < result.first) result.first = r;
            if (r > result.second) result.second = r;
        }
    }
    return result;
}

SInterval bfSignedOr(const SInterval& a, const SInterval& b)
{
    SInterval result{std::numeric_limits<int>::max(), std::numeric_limits<int>::min()};
    for (int i = a.first; i <= a.second; i++) {
        for (int j = b.first; j <= b.second; j++) {
            int r = i | j;
            if (r < result.first) result.first = r;
            if (r > result.second) result.second = r;
        }
    }
    return result;
}

// SInterval smartSignedOr(const SInterval& a, const SInterval& b)
// {
//     return bfSignedOr(a, b);
// }

//==============================================================================
// main algorithm
UInterval    operator+(const UInterval& a, unsigned int offset);
UInterval    operator-(const UInterval& a, unsigned int offset);
unsigned int loOr2(UInterval a, UInterval b);
unsigned int hiOr2(UInterval a, UInterval b);

// split interval according to its msb
std::tuple<unsigned int, UInterval, UInterval> splitInterval(UInterval x);

UInterval smartUnsignedOr(const UInterval& a, const UInterval& b)
{
    // std::cout << "smartUnsignedOr(" << a << ", " << b << ")" << std::endl;
    if (a == UInterval{0, 0}) return b;
    if (b == UInterval{0, 0}) return a;
    if (empty(a)) return a;
    if (empty(b)) return b;
    UInterval r{loOr2(a, b), hiOr2(a, b)};
    // std::cout << "smartUnsignedOr(" << a << ", " << b << ") = " << r << std::endl;
    return r;
}

//==============================================================================
unsigned int hiOr2(UInterval a, UInterval b);

static bool contains(const UInterval& i, unsigned int x)
{
    return (i.first <= x) && (x <= i.second);
}

unsigned int TRACEDhiOr2(UInterval a, UInterval b)
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

unsigned int hiOr2(UInterval a, UInterval b)
{
    // std::cout << "hiOr2(" << a << ", " << b << ")" << std::endl;
    unsigned int r = TRACEDhiOr2(a, b);
    // std::cout << "hiOr2(" << a << ", " << b << ") = " << r << std::endl;
    return r;
}

unsigned int loOr2(UInterval a, UInterval b)
{
    // simple cases
    if (a.first == 0 && a.second == 0) return b.first;
    if (b.first == 0 && b.second == 0) return a.first;

    auto [ma, a0, a1] = splitInterval(a);
    auto [mb, b0, b1] = splitInterval(b);

    assert(ma != 0 && mb != 0);

    // if (ma == 0) return b.first;
    // if (mb == 0) return a.first;
    if (ma > mb) {
        if (empty(a0)) return loOr2(a - ma, b) | ma;
        return loOr2(a0, b);
    }
    if (mb > ma) {
        if (empty(b0)) return loOr2(a, b - mb) | mb;
        return loOr2(a, b0);
    }
    // mb == ma
    if (empty(a0)) return loOr2(a - ma, b) | ma;
    if (empty(b0)) return loOr2(a, b - mb) | mb;
    return loOr2(a0, b0);
}

//==============================================================================
// details

UInterval operator+(const UInterval& a, unsigned int offset)
{
    return {a.first + offset, a.second + offset};
}

UInterval operator-(const UInterval& a, unsigned int offset)
{
    return {a.first - offset, a.second - offset};
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
std::tuple<unsigned int, UInterval, UInterval> splitInterval(UInterval x);

std::tuple<unsigned int, UInterval, UInterval> TRACED_splitInterval(UInterval x)
{
    if (x.first == 0 && x.second == 0) return {0, {1, 0}, x};  // special case, no msb
    unsigned int m = msb32(x.second);
    if (m == 0) return {0, {1, 0}, x};
    return {m, {x.first, m - 1}, {m, x.second}};
}

std::tuple<unsigned int, UInterval, UInterval> splitInterval(UInterval x)
{
    // std::cout << "splitInterval(" << x << ")" << std::endl;
    auto r = TRACED_splitInterval(x);
    // std::cout << "splitInterval(" << x << ") = " << std::get<0>(r) << ", " << std::get<1>(r) << ", " <<
    // std::get<2>(r)
    //<< std::endl;
    return r;
}

static std::pair<UInterval, UInterval> signSplit(SInterval a)
{
    if (a.first >= 0)
        return {UInterval{1u, 0u}, UInterval{static_cast<unsigned int>(a.first), static_cast<unsigned int>(a.second)}};
    if (a.second < 0)
        return {UInterval{static_cast<unsigned int>(a.first), static_cast<unsigned int>(a.second)}, UInterval{1u, 0u}};
    return {UInterval{static_cast<unsigned int>(a.first), static_cast<unsigned int>(-1)},
            UInterval{0u, static_cast<unsigned int>(a.second)}};
}

static SInterval U2SInterval(UInterval a)
{
    if ((a.first > INT32_MAX) || (a.second <= INT32_MAX)) {
        return {int(a.first), int(a.second)};
    }
    return {INT32_MIN, INT32_MAX};
}

SInterval smartSignedOr(const SInterval& a, const SInterval& b)
{
    auto [an, ap] = signSplit(a);
    auto [bn, bp] = signSplit(b);
    std::cout << "signSplit(" << a << ") = " << an << ", " << ap << std::endl;
    std::cout << "signSplit(" << b << ") = " << bn << ", " << bp << std::endl;

    UInterval pp = smartUnsignedOr(ap, bp);
    UInterval bfpp = bfUnsignedOr(ap, bp);
    std::cout << "smartUnsignedOr(" << ap << ", " << bp << ") = " << pp << "--" << bfpp << std::endl;

    UInterval nn = smartUnsignedOr(an, bn);
    UInterval bfnn = bfUnsignedOr(an, bn);
    std::cout << "smartUnsignedOr(" << an << ", " << bn << ") = " << nn << "--" << bfnn  << std::endl;

    UInterval pn = smartUnsignedOr(ap, bn);
    UInterval bfpn = bfUnsignedOr(ap, bn);
    std::cout << "smartUnsignedOr(" << ap << ", " << bn << ") = " << pn << "--" << bfpn  << std::endl;

    UInterval np = smartUnsignedOr(an, bp);
    UInterval bfnp = bfUnsignedOr(an, bp);
    std::cout << "smartUnsignedOr(" << an << ", " << bp << ") = " << np << "--" << bfnp  << std::endl;


    std::cout << "toto2" << std::endl;

    SInterval s1 = U2SInterval(pp);
    SInterval s2 = U2SInterval(nn);
    SInterval s3 = U2SInterval(pn);
    SInterval s4 = U2SInterval(np);

    std::cout << "toto3" << std::endl;

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

#include <limits>

#include "Intervals.hh"

// computes bitwise not on UNUMervals by brute force
UInterval bfUnsignedNot(const UInterval& a)
{
    // r is empty by default
    UInterval r{std::numeric_limits<UNUM>::max(), 0};

    for (UNUM i = a.first; i <= a.second; ++i) {
        UNUM ni = ~i;
        if (ni < r.first) r.first = ni;
        if (ni > r.second) r.second = ni;
    }
    return r;
}

// computes bitwise not on UNUMervals by brute force
SInterval bfSignedNot(const SInterval& a)
{
    // r is empty by default
    SInterval r{SNUM_MAX, SNUM_MIN};

    for (int i = a.first; i <= a.second; ++i) {
        int ni = ~i;
        if (ni < r.first) r.first = ni;
        if (ni > r.second) r.second = ni;
    }
    return r;
}

UInterval smartUnsignedNot(const UInterval& a)
{
    return UInterval{(UNUM)(~a.second), (UNUM)(~a.first)};
}

SInterval smartSignedNot(const SInterval& a)
{
    return SInterval{(SNUM)(~a.second), (SNUM)(~a.first)};
}

void testUnsignedNot(UNUM lo, UNUM hi)
{
    UInterval a{lo, hi};
    UInterval r1 = bfUnsignedNot(a);
    UInterval r2 = smartUnsignedNot(a);
    UInterval r3 = smartUnsignedNot(r2);

    if (r1 == r2) {
        std::cout << "OK: " << a << " -> " << r1 << " -> " << r3 << std::endl;
    } else {
        std::cout << "ERROR: " << a << " -> " << r1 << " != " << r2 << std::endl;
    }
}

void testUnsignedNot(const UInterval& a)
{
    UInterval r1 = bfUnsignedNot(a);
    UInterval r2 = smartUnsignedNot(a);
    UInterval r3 = smartUnsignedNot(r2);

    if (r1 == r2) {
        std::cout << "OK: " << a << " -> " << r1 << " -> " << r3 << std::endl;
    } else {
        std::cout << "ERROR: " << a << " -> " << r1 << " != " << r2 << std::endl;
    }
}

void testSignedNot(SNUM lo, SNUM hi)
{
    SInterval a{lo, hi};
    SInterval r1 = bfSignedNot(a);
    SInterval r2 = smartSignedNot(a);
    if (r1 == r2) {
        std::cout << "OK: " << a << " -> " << r1 << std::endl;
    } else {
        std::cout << "ERROR: " << a << " -> " << r1 << " != " << r2 << std::endl;
    }
}

void testSignedNot(const SInterval& a)
{
    SInterval r1 = bfSignedNot(a);
    SInterval r2 = smartSignedNot(a);
    if (r1 == r2) {
        std::cout << "OK: " << a << " -> " << r1 << std::endl;
    } else {
        std::cout << "ERROR: " << a << " -> " << r1 << " != " << r2 << std::endl;
    }
}

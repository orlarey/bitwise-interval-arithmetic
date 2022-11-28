#include <limits>

#include "Intervals.hh"

// computes bitwise not on UNUMervals by brute force
UInterval bfUnsignedNot(const UInterval& a)
{
    // r is empty by default
    UInterval r{std::numeric_limits<unsigned int>::max(), 0};

    for (unsigned int i = a.first; i <= a.second; ++i) {
        unsigned int ni = ~i;
        if (ni < r.first) r.first = ni;
        if (ni > r.second) r.second = ni;
    }
    return r;
}

// computes bitwise not on UNUMervals by brute force
SInterval bfSignedNot(const SInterval& a)
{
    // r is empty by default
    SInterval r = SEmpty();

    for (int i = a.first; i <= a.second; ++i) {
        int ni = ~i;
        if (ni < r.first) r.first = ni;
        if (ni > r.second) r.second = ni;
    }
    return r;
}

UInterval smartUnsignedNot(const UInterval& a)
{
    return UInterval{(unsigned int)(~a.second), (unsigned int)(~a.first)};
}

SInterval smartSignedNot(const SInterval& a)
{
    return SInterval{(int)(~a.second), (int)(~a.first)};
}

void testUnsignedNot(unsigned int lo, unsigned int hi)
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

void testSignedNot(int lo, int hi)
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

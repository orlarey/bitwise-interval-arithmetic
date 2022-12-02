#pragma once
#include <iostream>
#include <utility>

namespace itv
{
//==============================================================================
// Definitions of signed and unsigned intervals for bitwise operations
//==============================================================================

// Intervals are represented as pairs of numbers.
template <typename T>
struct BitwiseInterval {
    T lo;
    T hi;
};

// We need signed and unisgned intervals
using SInterval = BitwiseInterval<int>;
using UInterval = BitwiseInterval<unsigned int>;

// Empty intervals represented by (.lo > .hi)
constexpr UInterval UEMPTY{UINT_MAX, 0};
constexpr SInterval SEMPTY{INT_MAX, INT_MIN};

//==============================================================================
// Predicates
//==============================================================================

// Empty intervals are intervals such that: lo > hi
template <typename T>
bool isEmpty(const BitwiseInterval<T>& i)
{
    return i.lo > i.hi;
}

// Equality of intervals.
template <typename T>
bool operator==(const BitwiseInterval<T>& a, const BitwiseInterval<T>& b)
{
    if (isEmpty(a)) return isEmpty(b);
    return (a.lo == b.lo) && (a.hi == b.hi);
}

//==============================================================================
// Printing
//==============================================================================

inline std::ostream& operator<<(std::ostream& os, const UInterval& x)
{
    if (isEmpty(x)) return os << "U[]";
    return os << "U[" << x.lo << ".." << x.hi << "]";
}

inline std::ostream& operator<<(std::ostream& os, const SInterval& x)
{
    if (isEmpty(x)) return os << "S[]";
    return os << "S[" << x.lo << ".." << x.hi << "]";
}

//==============================================================================
// Operations
//==============================================================================

// Union of intervals
template <typename T>
BitwiseInterval<T> operator+(const BitwiseInterval<T>& a, const BitwiseInterval<T>& b)
{
    if (isEmpty(a)) return b;
    if (isEmpty(b)) return a;
    return {std::min(a.lo, b.lo), std::max(a.hi, b.hi)};
}

/**
 * Split a signed interval into two unsigned intervals, for the negative and the positive part
 */
inline std::pair<UInterval, UInterval> signSplit(const SInterval& x)
{
    if (isEmpty(x)) return {UEMPTY, UEMPTY};
    if (x.hi < 0) return {{(unsigned int)(x.lo), (unsigned int)(x.hi)}, UEMPTY};
    if (x.lo >= 0) return {UEMPTY, {(unsigned int)(x.lo), (unsigned int)(x.hi)}};
    return {{(unsigned int)(x.lo), (unsigned int)(-1)}, {(unsigned int)(0), (unsigned int)(x.hi)}};
}

/**
 * Merge two unsigned intervals to form a signed interval
 */
inline SInterval signMerge(const UInterval& np, const UInterval& pp)
{
    if (isEmpty(np)) {
        if (isEmpty(pp)) return SEMPTY;
        return {(int)(pp.lo), (int)(pp.hi)};
    }
    if (isEmpty(pp)) {
        return {(int)(np.lo), (int)(np.hi)};
    }

    return {(int)(np.lo), (int)(pp.hi)};
}
UInterval bitwiseUnsignedNot(const UInterval& a);
SInterval bitwiseSignedNot(const SInterval& a);

UInterval bitwiseUnsignedOr(const UInterval& a, const UInterval& b);
SInterval bitwiseSignedOr(const SInterval& a, const SInterval& b);

UInterval bitwiseUnsignedAnd(const UInterval& a, const UInterval& b);
SInterval bitwiseSignedAnd(const SInterval& a, const SInterval& b);

UInterval bitwiseUnsignedXOr(const UInterval& a, const UInterval& b);
SInterval bitwiseSignedXOr(const SInterval& a, const SInterval& b);
}  // namespace itv

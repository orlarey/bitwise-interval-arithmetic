#pragma once

#include <iostream>  // std::cout
#include <utility>   // std::pair, std::make_pair

#include "Numbers.hh"

//==============================================================================
// Definitions
//==============================================================================

// Intervals are represented as pairs of numbers.
template <typename T>
// using Interval = std::pair<T, T>;
struct Interval {
    T first;
    T second;
};

// We need signed and unisgned intervals
using SInterval = Interval<SNUM>;
using UInterval = Interval<UNUM>;

//==============================================================================
// Operations
//==============================================================================

// Empty intervals are intervals such that: first > second
template <typename T>
bool empty(const Interval<T>& i)
{
    return i.first > i.second;
}

// Union of intervals
template <typename T>
Interval<T> operator+(const Interval<T>& a, const Interval<T>& b)
{
    if (empty(a)) return b;
    if (empty(b)) return a;
    return {std::min(a.first, b.first), std::max(a.second, b.second)};
}

// Equality of intervals.
template <typename T>
bool operator==(const Interval<T>& a, const Interval<T>& b)
{
    if (empty(a)) return empty(b);
    return (a.first == b.first) && (a.second == b.second);
}

// Printing intervals
inline std::ostream& operator<<(std::ostream& os, const UInterval& x)
{
    if (empty(x)) return os << "U[]";
    return os << "U[" << (unsigned int)(x.first) << ".." << (unsigned int)(x.second) << "]";
}

inline std::ostream& operator<<(std::ostream& os, const SInterval& x)
{
    if (empty(x)) return os << "S[]";
    return os << "S[" << (int)(x.first) << ".." << (int)(x.second) << "]";
}

inline UInterval UEmpty()
{
    return {(UNUM)(UNUM_MAX), (UNUM)(UNUM_MIN)};  // and empty unsigned interval
}

inline SInterval SEmpty()
{
    return {(SNUM)(SNUM_MAX), (SNUM)(SNUM_MIN)};  // and empty signed interval
}

/**
 * Split a signed interval into two unsigned intervals, for the negative and the positive part
 */
inline std::pair<UInterval, UInterval> signSplit(const SInterval& x)
{
    if (empty(x)) return {UEmpty(), UEmpty()};
    if (x.second < 0) return {{(UNUM)(x.first), (UNUM)(x.second)}, UEmpty()};
    if (x.first >= 0) return {UEmpty(), {(UNUM)(x.first), (UNUM)(x.second)}};
    return {{(UNUM)(x.first), (UNUM)(-1)}, {(UNUM)(0), (UNUM)(x.second)}};
}

/**
 * reveser of sign split
 */
inline SInterval signMerge(const UInterval& np, const UInterval& pp)
{
    if (empty(np)) {
        if (empty(pp)) return SEmpty();
        return {(SNUM)(pp.first), (SNUM)(pp.second)};
    }
    if (empty(pp)) {
        return {(SNUM)(np.first), (SNUM)(np.second)};
    }

    return {(SNUM)(np.first), (SNUM)(pp.second)};
}
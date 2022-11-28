#pragma once

#include <iostream>  // std::cout
#include <utility>   // std::pair, std::make_pair

// #include "Numbers.hh"

//==============================================================================
// Definitions
//==============================================================================

// Intervals are represented as pairs of numbers.
template <typename T>
struct Interval {
    T first;
    T second;
};

// We need signed and unisgned intervals
using SInterval = Interval<int>;
using UInterval = Interval<unsigned int>;

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
    return {UINT_MAX, 0};  // and empty unsigned interval
}

inline SInterval SEmpty()
{
    return {INT_MAX, INT_MIN};  // and empty signed interval
}

/**
 * Split a signed interval into two unsigned intervals, for the negative and the positive part
 */
inline std::pair<UInterval, UInterval> signSplit(const SInterval& x)
{
    // if (empty(x)) return {UEmpty(), UEmpty()};
    // if (x.second < 0) return {{(unsigned int)(x.first), (unsigned int)(x.second)}, UEmpty()};
    // if (x.first >= 0) return {UEmpty(), {(unsigned int)(x.first), (unsigned int)(x.second)}};
    // return {{(unsigned int)(x.first), (unsigned int)(-1)}, {(unsigned int)(0), (unsigned int)(x.second)}};
    if (empty(x)) return {UEmpty(), UEmpty()};
    if (x.second < 0) return {{(unsigned int)(x.first), (unsigned int)(x.second)}, UEmpty()};
    if (x.first >= 0) return {UEmpty(), {(unsigned int)(x.first), (unsigned int)(x.second)}};
    return {{(unsigned int)(x.first), (unsigned int)(-1)}, {(unsigned int)(0), (unsigned int)(x.second)}};
}

/**
 * reveser of sign split
 */
inline SInterval signMerge(const UInterval& np, const UInterval& pp)
{
    if (empty(np)) {
        if (empty(pp)) return SEmpty();
        return {(int)(pp.first), (int)(pp.second)};
    }
    if (empty(pp)) {
        return {(int)(np.first), (int)(np.second)};
    }

    return {(int)(np.first), (int)(pp.second)};
}
#pragma once

#include <iostream>  // std::cout
#include <utility>   // std::pair, std::make_pair

//==============================================================================
// Definitions
//==============================================================================

// Intervals are represented as pairs of numbers.
template <typename T>
//using Interval = std::pair<T, T>;
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
    return os << "U[" << x.first << ".." << x.second << "]";
}

inline std::ostream& operator<<(std::ostream& os, const SInterval& x)
{
    if (empty(x)) return os << "S[]";
    return os << "S[" << x.first << ".." << x.second << "]";
}

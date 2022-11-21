#pragma once

#include <iostream>  // std::cout
#include <utility>   // std::pair, std::make_pair

// Intervals are represented as pairs of numbers.
template <typename T>
using Interval = std::pair<T, T>;

using UInterval = Interval<unsigned int>;
using SInterval = Interval<int>;

// convention for empty interval: first > second
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
    return std::make_pair(std::min(a.first, b.first), std::max(a.second, b.second));
}

// Equality of intervals.
template <typename T>
bool operator==(const Interval<T>& a, const Interval<T>& b)
{
    if (empty(a)) return empty(b);
    return (a.first == b.first) && (a.second == b.second);
}

// Printing intervals
template <typename T>
std::ostream& operator<<(std::ostream& os, const Interval<T>& x)
{
    if (empty(x)) return os << "[]";
    return os << "[" << x.first << ", " << x.second << "]";
}

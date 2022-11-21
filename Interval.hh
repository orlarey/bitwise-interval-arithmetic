#include <iostream>  // std::cout
#include <utility>   // std::pair, std::make_pair

// Intervals are represented as pairs of numbers.
template <typename T>
using Interval = std::pair<T, T>;

using UInterval = Interval<unsigned int>;
using SInterval = Interval<int>;

// convention for empty interval: first > second
template <typename T>
bool empty(const Interval<T>& i);

// Union of intervals.
template <typename T>
Interval<T> operator+(const Interval<T>& a, const Interval<T>& b);

// Equality of intervals.
template <typename T>
bool operator==(const Interval<T>& a, const Interval<T>& b);

// Printing intervals
template <typename T>
std::ostream& operator<<(std::ostream& os, const Interval<T>& x);

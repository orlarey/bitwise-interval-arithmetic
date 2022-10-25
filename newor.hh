#include <iostream>  // std::cout
#include <string>    // std::string
#include <utility>   // std::pair, std::make_pair

typedef std::pair<unsigned int, unsigned int> Interval;

// return the union of two intervals
Interval operator+(const Interval& a, const Interval& b);

// msb: most significant bit
unsigned int msb32(unsigned int x);

bool canSplitInterval(Interval x, Interval& a, Interval& b);
void testSplitInterval(Interval x);
void testNewOr(Interval a, Interval b);
Interval newor(Interval a, Interval b);

std::ostream& operator<<(std::ostream& os, const Interval& x);

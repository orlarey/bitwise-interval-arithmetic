#include "newand.hh"
#include "negation.hh"

UInterval newNot(UInterval a)
{
    return {~a.second, ~a.first};
}

UInterval newAnd(UInterval a, UInterval b)
{
    UInterval na = newNot(a);
    UInterval nb = newNot(b);
    UInterval nr = unsignedOr(na, nb);
    UInterval r  = newNot(nr);
    return r;
}
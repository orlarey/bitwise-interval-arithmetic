#include "newand.hh"
#include "negation.hh"

UInterval newUnsignedNot(UInterval a)
{
    return {~a.second, ~a.first};
}

UInterval newUnsignedAnd(UInterval a, UInterval b)
{
    UInterval na = newUnsignedNot(a);
    UInterval nb = newUnsignedNot(b);
    UInterval nr = unsignedOr(na, nb);
    UInterval r  = newUnsignedNot(nr);
    return r;
}
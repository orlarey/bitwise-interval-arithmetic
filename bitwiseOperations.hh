#pragma once
#include "bitwiseIntervals.hh"

namespace itv
{
UInterval bitwiseUnsignedNot(const UInterval& a);
SInterval bitwiseSignedNot(const SInterval& a);

UInterval bitwiseUnsignedOr(const UInterval& a, const UInterval& b);
SInterval bitwiseSignedOr(const SInterval& a, const SInterval& b);

UInterval bitwiseUnsignedAnd(const UInterval& a, const UInterval& b);
SInterval bitwiseSignedAnd(const SInterval& a, const SInterval& b);

UInterval bitwiseUnsignedXOr(const UInterval& a, const UInterval& b);
SInterval bitwiseSignedXOr(const SInterval& a, const SInterval& b);
}  // namespace itv

#pragma once
#include "Variable.h"
#include "ScalarSubtraction.h"
#include "ScalarSum.h"

template<class real>
ScalarSubtraction<real> operator-(const Scalar<real>& rhs, const Scalar<real>& lhs)
{
   return ScalarSubtraction<real>(rhs, lhs);
}

template<class real>
ScalarSum<real> operator+(const Scalar<real>& rhs, const Scalar<real>& lhs)
{
   return ScalarSum<real>(rhs, lhs);
}
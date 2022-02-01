#pragma once
#include "ScalarBinaryOperation.h"

template <class real>
class ScalarSum : public ScalarBinaryOperation<real>
{
public:
   ScalarSum(Scalar<real>& a, Scalar<real>& b);
   real compute(map<string, real>& variableValues) override;
};

template<class real>
inline ScalarSum<real>::ScalarSum(Scalar<real>& a, Scalar<real>& b) :ScalarBinaryOperation<real>(a, b)
{

}

template<class real>
inline real ScalarSum<real>::compute(map<string, real>& variableValues)
{
   return ScalarBinaryOperation<real>::_a->compute(variableValues) + ScalarBinaryOperation<real>::_b->compute(variableValues);
}

template<class real>
Scalar<real>* operator+(Scalar<real>& rhs, Scalar<real>& lhs)
{
   return new ScalarSum<real>(rhs, lhs);
}

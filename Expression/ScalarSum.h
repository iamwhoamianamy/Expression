#pragma once
#include "ScalarBinaryOperation.h"

template <class real>
class ScalarSum : public ScalarBinaryOperation<real>
{
public:
   ScalarSum(const Scalar<real>& a, const Scalar<real>& b);
   real compute(const map<string, real>& variableValues) const override;
};

template<class real>
inline ScalarSum<real>::ScalarSum(const Scalar<real>& a, const Scalar<real>& b) :
   ScalarBinaryOperation<real>(a, b) {}

template<class real>
inline real ScalarSum<real>::compute(const map<string, real>& variableValues) const
{
   return ScalarBinaryOperation<real>::_a->compute(variableValues) + 
          ScalarBinaryOperation<real>::_b->compute(variableValues);
}
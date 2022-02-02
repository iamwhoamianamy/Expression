#pragma once
#include "ScalarBinaryOperation.h"

template <class real>
class ScalarMultiplication : public ScalarBinaryOperation<real>
{
public:
   ScalarMultiplication(const Scalar<real>& a, const Scalar<real>& b);
   real compute(const map<string, real>& variableValues) const override;
};

template<class real>
inline ScalarMultiplication<real>::ScalarMultiplication(const Scalar<real>& a, const Scalar<real>& b) :
   ScalarBinaryOperation<real>(a, b) {}

template<class real>
inline real ScalarMultiplication<real>::compute(const map<string, real>& variableValues) const
{
   return ScalarBinaryOperation<real>::_a->compute(variableValues) *
      ScalarBinaryOperation<real>::_b->compute(variableValues);
}
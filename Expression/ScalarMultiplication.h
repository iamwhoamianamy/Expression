#pragma once
#include "ScalarBinaryOperation.h"

template <class real>
class ScalarMultiplication : public ScalarBinaryOperation<real>
{
public:
   ScalarMultiplication(const Scalar<real>* a, const Scalar<real>* b);
   real compute(const map<string, real>& variableValues) const override;
   virtual Scalar<real>* differentiate(const Scalar<real>* variable) const override;
};

template<class real>
inline ScalarMultiplication<real>::ScalarMultiplication(const Scalar<real>* a, const Scalar<real>* b) :
   ScalarBinaryOperation<real>(a, b) {}

template<class real>
inline real ScalarMultiplication<real>::compute(const map<string, real>& variableValues) const
{
   return ScalarBinaryOperation<real>::_a->compute(variableValues) *
          ScalarBinaryOperation<real>::_b->compute(variableValues);
}

template<class real>
inline Scalar<real>* ScalarMultiplication<real>::differentiate(const Scalar<real>* variable) const
{
   auto op1 = new ScalarMultiplication<real>(ScalarBinaryOperation<real>::_a->differentiate(variable),
                                             ScalarBinaryOperation<real>::_b);

   auto op2 = new ScalarMultiplication<real>(ScalarBinaryOperation<real>::_b->differentiate(variable),
                                             ScalarBinaryOperation<real>::_a);

   return new ScalarSum<real>(op1, op2);
}

#pragma once
#include "ScalarBinaryOperation.h"

template <class real>
class ScalarSum : public ScalarBinaryOperation<real>
{
public:
   ScalarSum(const Scalar<real>* a, const Scalar<real>* b);
   real compute(const map<string, real>& variableValues) const override;
   virtual Scalar<real>* differentiate(const Scalar<real>* variable) const override;
};

template<class real>
inline ScalarSum<real>::ScalarSum(const Scalar<real>* a, const Scalar<real>* b) :
   ScalarBinaryOperation<real>(a, b) {}

template<class real>
inline real ScalarSum<real>::compute(const map<string, real>& variableValues) const
{
   return ScalarBinaryOperation<real>::_a->compute(variableValues) + 
          ScalarBinaryOperation<real>::_b->compute(variableValues);
}

template<class real>
inline Scalar<real>* ScalarSum<real>::differentiate(const Scalar<real>* variable) const
{
   return new ScalarSum(ScalarBinaryOperation<real>::_a->differentiate(variable),
                        ScalarBinaryOperation<real>::_b->differentiate(variable));
}

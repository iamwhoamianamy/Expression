#pragma once
#include "ScalarBinaryOperation.h"

template <class real>
class ScalarSubtraction : public ScalarBinaryOperation<real>
{
public:
   ScalarSubtraction(const Scalar<real>* a, const Scalar<real>* b);
   real compute(const map<string, real>& variableValues) const override;
   virtual Scalar<real>* differentiate(const Scalar<real>* variable) const override;
};

template<class real>
inline ScalarSubtraction<real>::ScalarSubtraction(const Scalar<real>* a, const Scalar<real>* b) :
   ScalarBinaryOperation<real>(a, b) {}

template<class real>
inline real ScalarSubtraction<real>::compute(const map<string, real>& variableValues) const
{
   return ScalarBinaryOperation<real>::_a->compute(variableValues) -
          ScalarBinaryOperation<real>::_b->compute(variableValues);
}

template<class real>
inline Scalar<real>* ScalarSubtraction<real>::differentiate(const Scalar<real>* variable) const
{
   return new ScalarSubtraction(ScalarBinaryOperation<real>::_a->differentiate(variable),
                                ScalarBinaryOperation<real>::_b->differentiate(variable));
}

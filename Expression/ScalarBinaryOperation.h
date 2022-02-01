#pragma once
#include "Scalar.h"

template <class real>
class ScalarBinaryOperation : public Scalar<real>
{
protected:
   const Scalar<real>* _a;
   const Scalar<real>* _b;

public:
   ScalarBinaryOperation(const Scalar<real>& a, const Scalar<real>& b);
   virtual real compute(const map<string, real>& variableValues) const = 0;
};

template<class real>
inline ScalarBinaryOperation<real>::ScalarBinaryOperation(
   const Scalar<real>& a, const Scalar<real>& b) : _a(&a), _b(&b) {}
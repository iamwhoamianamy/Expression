#pragma once
#include "Scalar.h"

template <class real>
class ScalarBinaryOperation : public Scalar<real>
{
protected:
   Scalar<real>* _a;
   Scalar<real>* _b;

public:
   ScalarBinaryOperation(Scalar<real>& a, Scalar<real>& b);
   virtual real compute(map<string, real>& variableValues) = 0;
};

template<class real>
inline ScalarBinaryOperation<real>::ScalarBinaryOperation(Scalar<real>& a, Scalar<real>& b)
{
   _a = &a;
   _b = &b;
}


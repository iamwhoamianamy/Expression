#pragma once
#include "Scalar.h"

template <class real>
class ScalarBinaryOperation : public Scalar<real>
{
protected:
   const Scalar<real>* _a;
   const Scalar<real>* _b;

public:
   ScalarBinaryOperation(const Scalar<real>* a, const Scalar<real>* b);
   virtual real compute(const map<string, real>& variableValues) const override = 0;
   virtual Scalar<real>* differentiate(const Scalar<real>* variable) const override = 0;
private:
   virtual bool isEqual(const Scalar<real>* other) const;
};

template<class real>
inline ScalarBinaryOperation<real>::ScalarBinaryOperation(
   const Scalar<real>* a, const Scalar<real>* b) : _a(a), _b(b) {}

template<class real>
inline bool ScalarBinaryOperation<real>::isEqual(const Scalar<real>* other) const
{
   return _a == static_cast<const ScalarBinaryOperation&>(*other)._a &&
          _b == static_cast<const ScalarBinaryOperation&>(*other)._b;
}

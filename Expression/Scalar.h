#pragma once
#include "Expression.h"

template <class real>
class Scalar : public Expression<real>
{
public:
   virtual real compute(const map<string, real>& variableValues) const = 0;
   Scalar<real>* plus(const Scalar<real>* other) const;
   Scalar<real>* minus(const Scalar<real>* other) const;
   Scalar<real>* mult(const Scalar<real>* other) const;
   virtual Scalar<real>* differentiate(const Scalar<real>* variable) const = 0;
   bool operator==(const Scalar<real>* other) const;
private:
   virtual bool isEqual(const Scalar<real>* other) const = 0;
};

template<class real>
class ScalarSum;

template<class real>
class ScalarSubtraction;

template<class real>
class ScalarMultiplication;

template<class real>
inline Scalar<real>* Scalar<real>::plus(const Scalar<real>* other) const
{
   return new ScalarSum<real>(this, other);
}

template<class real>
inline Scalar<real>* Scalar<real>::minus(const Scalar<real>* other) const
{
   return new ScalarSubtraction<real>(this, other);
}

template<class real>
inline Scalar<real>* Scalar<real>::mult(const Scalar<real>* other) const
{
   return new ScalarMultiplication<real>(this, other);
}

template<class real>
inline bool Scalar<real>::operator==(const Scalar<real>* other) const
{
   return typeid(*this) == typeid(*other) && isEqual(other);
}

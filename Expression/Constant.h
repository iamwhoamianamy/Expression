#pragma once
#include "Scalar.h"

template <class real>
class Constant : public Scalar<real>
{
private:
   const real _value;
public:
   Constant<real>(const real value);
   real compute(const map<string, real>& variableValues) const override;
   virtual Scalar<real>* differentiate(const Scalar<real>* variable) const override;
private:
   virtual bool isEqual(const Scalar<real>* other) const;
};

template<class real>
inline Constant<real>::Constant(const real value) : _value(value) {}

template <class real>
inline real Constant<real>::compute(const map<string, real>& variableValues) const
{
   return _value;
}

template<class real>
inline Scalar<real>* Constant<real>::differentiate(const Scalar<real>* variable) const
{
   return new Constant<real>(0);
}

template<class real>
inline bool Constant<real>::isEqual(const Scalar<real>* other) const
{
   return _value == static_cast<const Constant&>(*other)._value;
}
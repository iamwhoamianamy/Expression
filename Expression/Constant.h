#pragma once
#include "Scalar.h"

template <class real>
class Constant : public Scalar<real>
{
private:
   const string _name;
public:
   Constant<real>(const real);
   Constant<real>(const string name);
   real compute(const map<string, real>& ConstantValues) const override;
};

template<class real>
inline Constant<real>::Constant(const real) : _name(to_string(real)) {}

template <class real>
inline Constant<real>::Constant(const string name) : _name(name) {}

template <class real>
inline real Constant<real>::compute(const map<string, real>& ConstantValues) const
{
   auto res = *ConstantValues.find(_name);

   return res.second;
}
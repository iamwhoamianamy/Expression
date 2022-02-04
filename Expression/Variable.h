#pragma once
#include "Scalar.h"
#include "Constant.h"

template <class real>
class Variable : public Scalar<real>
{
private:
   const string _name;
public:
   Variable<real>(const string name);
   real compute(const map<string, real>& variableValues) const override;
   virtual Scalar<real>* differentiate(const Scalar<real>* variable) const override;
private:
   virtual bool isEqual(const Scalar<real>* other) const;
};

template <class real>
inline Variable<real>::Variable(const string name) : _name(name) {}

template <class real>
inline real Variable<real>::compute(const map<string, real>& variableValues) const
{
   auto res = *variableValues.find(_name);

   return res.second;
}

template<class real>
inline Scalar<real>* Variable<real>::differentiate(const Scalar<real>* variable) const
{
   return new Constant<real>(this == variable ? 1 : 0) ;
}

template<class real>
inline bool Variable<real>::isEqual(const Scalar<real>* other) const
{
   return _name == static_cast<const Variable&>(*other)._name;
}

#pragma once
#include "Scalar.h"

template <class real>
class Variable : public Scalar<real>
{
private:
   const string _name;
public:
   Variable<real>(const string name);
   real compute(const map<string, real>& variableValues) const override;
};

template <class real>
inline Variable<real>::Variable(const string name) : _name(name) {}

template <class real>
inline real Variable<real>::compute(const map<string, real>& variableValues) const
{
   auto res = *variableValues.find(_name);

   return res.second;
}
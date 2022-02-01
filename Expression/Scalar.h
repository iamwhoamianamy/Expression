#pragma once
#include "Expression.h"

template <class real>
class Scalar : public Expression<real>
{
public:
   virtual real compute(map<string, real>& variableValues) = 0;
};

template <class real>
class Variable : public Scalar<real>
{
private:
   string _name;
public:
   Variable<real>(string name);
   real compute(map<string, real>& variableValues) override;
};

template<class real>
inline Variable<real>::Variable(string name)
{
   _name = name;
}
template <class real>
inline real Variable<real>::compute(map<string, real>& variableValues)
{
   return variableValues[_name];
}


#pragma once
#include "Expression.h"

template <class real>
class Scalar : public Expression<real>
{
public:
   virtual real compute(const map<string, real>& variableValues) const = 0;
};
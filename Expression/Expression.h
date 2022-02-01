#pragma once
#include <map>
#include <string>

using namespace std;

template <class real>
class Expression
{
public:
   Expression() {}
   virtual real compute(const map<string, real>& variableValues) const = 0;
};
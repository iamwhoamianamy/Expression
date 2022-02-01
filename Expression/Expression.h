#pragma once
#include <map>
#include <string>

using namespace std;

template <class real>
class Expression
{
public:
   Expression() {}
   virtual real compute(map<string, real>& variableValues) = 0;
};
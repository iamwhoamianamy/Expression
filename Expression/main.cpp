#include <iostream>
#include <map>
#include "Scalar.h"
#include "ScalarBinaryOperation.h"
#include "ScalarSum.h"

int main()
{
   map<string, double> variableNames;
   variableNames["a"] = 3;
   variableNames["b"] = 10;

   Variable<double> a("a");
   Variable<double> b("b");
   //Scalar<double>* exp = new ScalarSum<double>(a, b);
   Scalar<double>* exp = a + b;

   cout << exp->compute(variableNames);

}
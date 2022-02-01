#include <iostream>
#include <map>
#include "ScalarArythmetics.h"

int main()
{
   map<string, double> variableNames;
   variableNames["a"] = 3;
   variableNames["b"] = 10;
   variableNames["c"] = 5;
   variableNames["d"] = 4;

   Variable<double> a("a");
   Variable<double> b("b");
   Variable<double> c("c");
   Variable<double> d("d");
   //Scalar<double>* exp = new ScalarSum<double>(a, b);
   auto res = a + b - c;

   cout << res.compute(variableNames);

}
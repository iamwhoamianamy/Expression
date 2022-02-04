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

   Scalar<double>* a = new Variable<double>("a");
   Scalar<double>* b = new Variable<double>("b");
   Scalar<double>* c = new Variable<double>("c");
   Scalar<double>* d = new Variable<double>("d");

   //auto res = a->plus(b)->minus(c)->mult(d)->mult(new Constant<double>(10));
   auto exp = a->mult(new Constant<double>(4))->mult(a)->plus(a);
   auto res = exp->differentiate(a);

   cout << res->compute(variableNames);
}
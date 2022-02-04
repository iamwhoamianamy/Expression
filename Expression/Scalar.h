#pragma once
#include "Expression.h"
#include <sstream>
#include <stack>

template <class real>
class Scalar : public Expression<real>
{
public:
   virtual real compute(const map<string, real>& variableValues) const = 0;
   static Scalar<real>* parse(const string& str);
   Scalar<real>* plus(const Scalar<real>* other) const;
   Scalar<real>* minus(const Scalar<real>* other) const;
   Scalar<real>* mult(const Scalar<real>* other) const;
   virtual Scalar<real>* differentiate(const Scalar<real>* variable) const = 0;
   bool operator==(const Scalar<real>* other) const;
private:
   virtual bool isEqual(const Scalar<real>* other) const = 0;
};

template<class real>
class ScalarSum;

template<class real>
class ScalarSubtraction;

template<class real>
class ScalarMultiplication;

template<class real>
class Constant;

template<class real>
class Variable;

template<class real>
Scalar<real>* Scalar<real>::parse(const string& str)
{
   stringstream stream;
   stream.str(str);

   stack<Scalar<real>*> operands;
   stack<char> operators;
   string symbol;

   while(stream >> symbol)
   {
      real value;
      try
      {
         real value = stod(symbol);
         auto op = new Constant<real>(value);
         operands.push(op);

         continue;
      }
      catch (exception ex) { }

      if(symbol == ")")
      {
         char operand = operators.top();
         operators.pop();

         Scalar<real>* right = operands.top();
         operands.pop();

         Scalar<real>* left = operands.top();
         operands.pop();

         switch(operand)
         {
            case '+':
            {
               operands.push(new ScalarSum<real>(left, right));
               break;
            }
            case '*':
            {
               operands.push(new ScalarMultiplication<real>(left, right));
               break;
            }
            case '-':
            {
               operands.push(new ScalarSubtraction<real>(left, right));
               break;
            }
            default:
               break;
         }
      }
      else
      {
         if(symbol == "+" || symbol == "-" || symbol == "*")
         {
            operators.push(symbol[0]);
         }
         else
         {
            if(symbol == "(")
            {

            }
            else
            {
               operands.push(new Variable<real>(symbol));
            }
         }
      }
   }

   Scalar<real>* res = operands.top();
   operands.pop();

   return res;
}

template<class real>
inline Scalar<real>* Scalar<real>::plus(const Scalar<real>* other) const
{
   return new ScalarSum<real>(this, other);
}

template<class real>
inline Scalar<real>* Scalar<real>::minus(const Scalar<real>* other) const
{
   return new ScalarSubtraction<real>(this, other);
}

template<class real>
inline Scalar<real>* Scalar<real>::mult(const Scalar<real>* other) const
{
   return new ScalarMultiplication<real>(this, other);
}

template<class real>
inline bool Scalar<real>::operator==(const Scalar<real>* other) const
{
   return typeid(*this) == typeid(*other) && isEqual(other);
}

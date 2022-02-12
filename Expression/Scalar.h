#pragma once
#include "Expression.h"
#include "ScalarClasses.h"
#include "ScalarParser.h"

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
   Scalar<real>* differentiate(const string& variable) const;
   bool operator==(const Scalar<real>* other) const;
private:
   virtual bool isEqual(const Scalar<real>* other) const = 0;
};


template<class real>
Scalar<real>* Scalar<real>::parse(const string& str)
{
   ScalarParser<real> scalarParser;
   return scalarParser.parse(str);
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
inline Scalar<real>* Scalar<real>::differentiate(const string& variable) const
{
   return differentiate(new Variable<real>(variable));
}

template<class real>
inline bool Scalar<real>::operator==(const Scalar<real>* other) const
{
   return typeid(*this) == typeid(*other) && isEqual(other);
}

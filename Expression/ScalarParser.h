#pragma once
#include <sstream>
#include <queue>
#include <stack>
#include "ScalarArythmetics.h"

template<class T>
class PairComparator
{
public:
   bool operator() (pair<T, int>& p1, pair<T, int>& p2)
   {
      return p1.second < p2.second;
   }
};

template<class real>
class ScalarParser
{
private:
   priority_queue<pair<Scalar<real>*, int>, vector<pair<Scalar<real>*, int>>, PairComparator<Scalar<real>*>> operands;
   priority_queue<pair<string, int>, vector<pair<string, int>>, PairComparator<string>> operators;
   vector<string> possibleOperators = { "+", "-", "*" };
   vector<string> separators = { "(", ")" };
   int priority = 0;
public:
   ScalarParser<real>();
   Scalar<real>* parse(const string& str);
private:
   string formEasyToParseString(const string& str);
   string formEasyToParseStringEntry(const string& letter);
   void translateToPolishNotation(const string& str);
   Scalar<real>* formScalarFromPolishNotation();
   void reactToToken(const string& token);
   bool changePriority(const string& token);
   void addEntryToPolishNotation(const string& token);
   Scalar<real>* formScalarFormOperandToken(const string& token);
   Scalar<real>* formScalarFromOperatorToken(const string& token);
   pair<Scalar<real>*, Scalar<real>*> getTwoOperands();
};


template<class real>
inline ScalarParser<real>::ScalarParser()
{

}

template<class real>
inline Scalar<real>* ScalarParser<real>::parse(const string& str)
{
   string easyToParseString = formEasyToParseString(str);
   translateToPolishNotation(easyToParseString);
   return formScalarFromPolishNotation();
}

template<class real>
inline string ScalarParser<real>::formEasyToParseString(const string& str)
{
   string result = "(";

   for(auto letter : str)
   {
      result += formEasyToParseStringEntry(string(1, letter));
   }

   return result + ")";
}

template<class real>
inline string ScalarParser<real>::formEasyToParseStringEntry(const string& letter)
{
   auto potentialSeparator1 = find(separators.begin(), separators.end(), letter);
   if(potentialSeparator1 != separators.end())
   {
      return " " + letter + " ";
   }

   auto potentialSeparator2 = find(possibleOperators.begin(), possibleOperators.end(), letter);
   if(potentialSeparator2 != possibleOperators.end())
   {
      return " " + letter + " ";
   }

   return letter;
}

template<class real>
inline void ScalarParser<real>::translateToPolishNotation(const string& str)
{
   stringstream stream;
   stream.str(str);
   string token;

   while(stream >> token)
   {
      reactToToken(token);
   }
}

template<class real>
inline void ScalarParser<real>::reactToToken(const string& token)
{
   if(!changePriority(token))
      addEntryToPolishNotation(token);
}

template<class real>
inline bool ScalarParser<real>::changePriority(const string& token)
{
   if(token == "(")
   {
      priority++;
      return true;
   }

   if(token == ")")
   {
      priority--;
      return true;
   }

   return false;
}

template<class real>
inline void ScalarParser<real>::addEntryToPolishNotation(const string& token)
{
   auto potentialOperator = find(possibleOperators.begin(), possibleOperators.end(), token);

   if(potentialOperator != possibleOperators.end())
   {
      auto operatorsEntry = make_pair<string, int>(string(token), int(priority));
      operators.push(operatorsEntry);
   }
   else
   {
      auto operandsEntry = make_pair<Scalar<real>*, int>(formScalarFormOperandToken(token), int(priority));
      operands.push(operandsEntry);
   }
}

template<class real>
inline Scalar<real>* ScalarParser<real>::formScalarFormOperandToken(const string& token)
{
   real value;

   try
   {
      real value = stod(token);
      return new Constant<real>(value);
   }
   catch(exception ex)
   {

   }

   return new Variable<real>(token);
}

template<class real>
inline Scalar<real>* ScalarParser<real>::formScalarFromPolishNotation()
{
   while(!operators.empty())
   {
      string currentOperator = operators.top().first;
      operators.pop();

      auto operandsEntry = make_pair<Scalar<real>*, int>(formScalarFromOperatorToken(currentOperator), int(priority));
      operands.push(operandsEntry);
   }

   return operands.top().first;
}


template<class real>
inline Scalar<real>* ScalarParser<real>::formScalarFromOperatorToken(const string& token)
{
   switch(token[0])
   {
      case '+':
      {
         auto twoOperands = getTwoOperands();
         return new ScalarSum<real>(twoOperands.first, twoOperands.second);
      }
      case '-':
      {
         auto twoOperands = getTwoOperands();
         return new ScalarSubtraction<real>(twoOperands.first, twoOperands.second);
      }
      case '*':
      {
         auto twoOperands = getTwoOperands();
         return new ScalarMultiplication<real>(twoOperands.first, twoOperands.second);
      }
      default:
         break;
   }
}

template<class real>
inline pair<Scalar<real>*, Scalar<real>*> ScalarParser<real>::getTwoOperands()
{
   auto operand1 = operands.top().first;
   operands.pop();
   auto operand2 = operands.top().first;
   operands.pop();

   return pair<Scalar<real>*, Scalar<real>*>(operand1, operand2);
}

#pragma once

#include <map>
#include <vector>
#include <string>
#include "Statement.hpp"
#include "Variable.hpp"
using namespace std;

class Interpretor
{
public:
    void debugPrint() const;
    void interpreat(vector<Statement> statements);
private:
    map<string, Variable> mVariables;
    void variableAssignment(Statement Statement);
    optional<Variable> expressionValue(Statement statement);
    void returnValue(Statement Statement);
    bool compatibleTypeforOperation(Type type1,Type type2,string op);
    Variable oprateOnVaribles(Variable var1,Variable var2,string op);
};

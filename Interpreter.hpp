#pragma once

#include <vector>
#include <string>
#include "Statement.hpp"
#include "Variable.hpp"
using namespace std;

class Interpretor
{
public:

private:
    vector<Variable> variables;
    variableValue expressionValue(Statement statement);
    variableValue returnValue(Statement Statement);
};

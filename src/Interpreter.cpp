
#include "Interpreter.hpp"
#include "Variable.hpp"
#include <iostream>

void Interpretor::variableAssignment(Statement statement)
{
    Variable newVariable;
    if (statement.mParameters[0].mKind == StatementKind::INT_LITERAL)
    {
        newVariable.type = Type("INT", BUILTIN_TYPE::INT);
        newVariable.INT = stol(statement.mParameters[0].mName);
        newVariable.mName = statement.mName;
        mVariables[newVariable.mName] = newVariable;
        return;
    }
    if (statement.mParameters[0].mKind == StatementKind::STRING_LITERAL)
    {
        newVariable.type = Type("STRING", BUILTIN_TYPE::STRING);
        newVariable.STRING = statement.mParameters[0].mName;
        newVariable.mName = statement.mName;
        mVariables[newVariable.mName] = newVariable;
        return;
    }
    if (statement.mParameters[0].mKind == StatementKind::DOUBLE_LITERAL)
    {
        newVariable.type = Type("DOUBLE", BUILTIN_TYPE::DOUBLE);
        newVariable.DOUBLE = stold(statement.mParameters[0].mName);
        newVariable.mName = statement.mName;
        mVariables[newVariable.mName] = newVariable;
        return;
    }
    if (statement.mParameters[0].mKind == StatementKind::OPERATOR_CALL)
    {
        newVariable = expressionValue(statement.mParameters[0]).value();
        newVariable.mName = statement.mName;
        mVariables[newVariable.mName] = newVariable;
        return;
    }
}

optional<Variable> Interpretor::expressionValue(Statement statement)
{
    Variable newVariable;
    if (statement.mKind == StatementKind::INT_LITERAL)
    {
        newVariable.type = Type("INT", BUILTIN_TYPE::INT);
        newVariable.INT = stol(statement.mName);
        newVariable.mName = statement.mName;
        return newVariable;
    }
    if (statement.mKind == StatementKind::STRING_LITERAL)
    {
        newVariable.type = Type("STRING", BUILTIN_TYPE::STRING);
        newVariable.STRING = statement.mName;
        newVariable.mName = statement.mName;
        return newVariable;
    }
    if (statement.mKind == StatementKind::DOUBLE_LITERAL)
    {
        newVariable.type = Type("DOUBLE", BUILTIN_TYPE::DOUBLE);
        newVariable.DOUBLE = stold(statement.mName);
        newVariable.mName = statement.mName;
        return newVariable;
    }
    if (statement.mKind == StatementKind::VARIABLE)
    {
        return mVariables[statement.mName];
    }
    if (statement.mKind == StatementKind::OPERATOR_CALL)
    {
        optional<Variable> lhs = expressionValue(statement.mParameters[0]);
        optional<Variable> rhs = expressionValue(statement.mParameters[1]);
        if (lhs.has_value() && rhs.has_value())
        {
            if (compatibleTypeforOperation(lhs.value().type, rhs.value().type, statement.mName))
            {
                return oprateOnVaribles(lhs.value(), rhs.value(), statement.mName);
            }
        }
    }
    return nullopt;
}

void Interpretor::debugPrint() const
{
    for (auto variables : mVariables)
    {
        variables.second.debugPrint();
    }
}
void Interpretor::interpreat(vector<Statement> statements)
{
    for (Statement statement : statements)
    {
        if (statement.mKind == StatementKind::VARIABLE_ASSIGNMENT)
        {
            variableAssignment(statement);
            continue;
        }
    }
}
// To do
// complete this function
bool Interpretor::compatibleTypeforOperation(Type type1, Type type2, string op)
{
    return true;
};

Variable Interpretor::oprateOnVaribles(Variable var1, Variable var2, string op)
{
    if (op == "+")
    {
        if (var1.type.mName == "STRING")
        {
            var1.STRING += var2.STRING;
            return var1;
        }
        double finalValue = 0;
        bool isDouble = false;

        if (var1.type.mName == "INT")
            finalValue += var1.INT;
        else
        {
            finalValue += var1.DOUBLE;
            isDouble = true;
        }

        if (var2.type.mName == "INT")
            finalValue += var2.INT;
        else
        {
            finalValue += var2.DOUBLE;
            isDouble = true;
        }
        if (isDouble)
        {
            var1.type = Type("DOUBLE", BUILTIN_TYPE::DOUBLE);
            var1.DOUBLE = finalValue;
            return var1;
        }
        var1.type = Type("INT", BUILTIN_TYPE::INT);
        var1.INT = (long long)finalValue;
        return var1;
    }
    if (op == "-")
    {
        double finalValue = 0;
        bool isDouble = false;
        if (var1.type.mName == "INT")
            finalValue += var1.INT;
        else
        {
            finalValue += var1.DOUBLE;
            isDouble = true;
        }
        if (var2.type.mName == "INT")
            finalValue -= var2.INT;
        else
        {
            finalValue -= var2.DOUBLE;
            isDouble = true;
        }
        if (isDouble)
        {
            var1.type = Type("DOUBLE", BUILTIN_TYPE::DOUBLE);
            var1.DOUBLE = finalValue;
            return var1;
        }
        var1.type = Type("INT", BUILTIN_TYPE::INT);
        var1.INT = (long long)finalValue;
        return var1;
    }
    if (op == "*")
    {
        double finalValue = 0;
        bool isDouble = false;
        if (var1.type.mName == "INT")
            finalValue += var1.INT;
        else
        {
            finalValue += var1.DOUBLE;
            isDouble = true;
        }
        if (var2.type.mName == "INT")
            finalValue *= var2.INT;
        else
        {
            finalValue *= var2.DOUBLE;
            isDouble = true;
        }
        if (isDouble)
        {
            var1.type = Type("DOUBLE", BUILTIN_TYPE::DOUBLE);
            var1.DOUBLE = finalValue;
            return var1;
        }
        var1.type = Type("INT", BUILTIN_TYPE::INT);
        var1.INT = (long long)finalValue;
        return var1;
    }
    if (op == "/")
    {
        double finalValue = 0;
        bool isDouble = false;
        if (var1.type.mName == "INT")
            finalValue += var1.INT;
        else
        {
            finalValue += var1.DOUBLE;
            isDouble = true;
        }
        if (var2.type.mName == "INT")
            finalValue /= var2.INT;
        else
        {
            finalValue /= var2.DOUBLE;
            isDouble = true;
        }
        if (isDouble)
        {
            var1.type = Type("DOUBLE", BUILTIN_TYPE::DOUBLE);
            var1.DOUBLE = finalValue;
            return var1;
        }
        var1.type = Type("INT", BUILTIN_TYPE::INT);
        var1.INT = (long long)finalValue;
        return var1;
    }
    if (op == "%")
    {
        var1.type = Type("INT", BUILTIN_TYPE::INT);
        var1.INT = var1.INT%var2.INT;
        return var1;
    }
};

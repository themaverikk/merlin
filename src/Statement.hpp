#pragma once

#include <string>
#include <vector>
#include "Type.hpp"

using namespace std;

enum class StatementKind : int
{
    VARIABLE_ASSIGNMENT,
    FUNCTION_CALL,
    LITERAL,
    INT_LITERAL,
    DOUBLE_LITERAL,
    STRING_LITERAL,
    OPERATOR_CALL,
    VARIABLE,
};

static const char *sStatementKindStrings[] = {
    "VARIABLE_ASSIGNMENT",
    "FUNCTION_CALL",
    "LITERAL",
    "INT_LITERAL",
    "DOUBLE_LITERAL",
    "STRING_LITERAL",
    "OPERATOR_CALL",
    "VARIABLE"
    };

class Statement
{
public:
    string mName;
    Type mType{Type("void", VOID)};
    vector<Statement> mParameters;
    StatementKind mKind{StatementKind::FUNCTION_CALL};

    void debugPrint(size_t indent);
};

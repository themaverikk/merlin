#include "Parser.hpp"
#include <iostream>

using namespace std;

struct OperatorEntry
{
    string mName;
    size_t mPrecedence;
};

static map<string, OperatorEntry> sOperators{
    // precedence 0 is reserved for "no operator".
    {"+", OperatorEntry{"+", 1}},
    {"-", OperatorEntry{"-", 1}},
    {"/", OperatorEntry{"/", 10}},
    {"*", OperatorEntry{"*", 10}},
    {"%", OperatorEntry{"%",10}}};

bool Parser::expectFunctionDefinition()
{
    vector<Token>::iterator parseStart = mCurrentToken;

    optional<Token> possibleName = expectIdentifier();

    if (possibleName.has_value())
    { // We have a name!
        optional<Token> possibleOperator = expectOperator("(");

        if (possibleOperator.has_value())
        { // We have a function!

            FunctionDefinition func;
            func.mName = possibleName->mText;

            while (!expectOperator(")").has_value())
            {
                optional<Token> possibleVariableName = expectIdentifier();

                ParameterDefinition param;
                if (possibleVariableName.has_value())
                {
                    param.mName = possibleVariableName->mText;
                }
                func.mParameters.push_back(param);

                if (expectOperator(")").has_value())
                {
                    break;
                }
                if (!expectOperator(",").has_value())
                {
                    throw runtime_error("Expected ',' to separate parameters or ')' to indicate end of argument list.at line no " + to_string(mCurrentToken->mLineNumber));
                }
            }

            optional<vector<Statement>> statements = parseFunctionBody();
            if (!statements.has_value())
            {
                mCurrentToken = parseStart;
                return false;
            }
            func.mStatements.insert(func.mStatements.begin(), statements->begin(), statements->end());

            mFunctions[func.mName] = func;

            return true;
        }
        else
        {
            mCurrentToken = parseStart;
        }
    }
    else
    {
        mCurrentToken = parseStart;
    }

    return false;
}

bool Parser::parseMainFunction()
{
    vector<Token>::iterator parseStart = mCurrentToken;
    optional<Statement> statement = expectStatement();
    if (!statement.has_value())
    {
        mCurrentToken = parseStart;
        return false;
    }
    mFunctions["main"].mStatements.push_back(statement.value());
    if (!expectOperator(";").has_value())
    {
        throw runtime_error("Expected ';' at end of statement.at line no " + to_string(mCurrentToken->mLineNumber));
    }
    return true;
}
void Parser::parse(vector<Token> &tokens)
{
    mEndToken = tokens.end();
    mCurrentToken = tokens.begin();
    // initializing the main func
    FunctionDefinition main;
    main.mName = "main";
    mFunctions["main"] = main;
    while (mCurrentToken != mEndToken)
    {
        if (expectIdentifier("fn"))
        {
            expectFunctionDefinition();
        }
        else if (parseMainFunction())
        {
        }
        else
        {
            cerr << "Unknown identifier " << mCurrentToken->mText << "." << endl;
            ++mCurrentToken;
        }
    }
}

optional<Token> Parser::expectIdentifier(const string &name)
{
    if (mCurrentToken == mEndToken)
    {
        return nullopt;
    }
    if (mCurrentToken->mType != IDENTIFIER)
    {
        return nullopt;
    }
    if (!name.empty() && mCurrentToken->mText != name)
    {
        return nullopt;
    }

    Token returnToken = *mCurrentToken;
    ++mCurrentToken;
    return returnToken;
}

optional<Token> Parser::expectOperator(const string &name)
{
    if (mCurrentToken == mEndToken)
    {
        return nullopt;
    }
    if (mCurrentToken->mType != OPERATOR)
    {
        return nullopt;
    }
    if (!name.empty() && mCurrentToken->mText != name)
    {
        return nullopt;
    }

    Token returnToken = *mCurrentToken;
    ++mCurrentToken;
    return returnToken;
}

Parser::Parser()
{
    mTypes["void"] = Type("void", VOID);
    mTypes["int"] = Type("signed int", INT32);
    mTypes["unsigned"] = Type("unsigned int", UINT32);
    mTypes["char"] = Type("signed char", INT8);
    mTypes["uint8_t"] = Type("uint8_t", INT8);
    mTypes["double"] = Type("double", DOUBLE);
}

optional<Type> Parser::expectType()
{
    optional<Token> possibleType = expectIdentifier();
    if (!possibleType)
    {
        return nullopt;
    }

    map<string, Type>::iterator foundType = mTypes.find(possibleType->mText);
    if (foundType == mTypes.end())
    {
        --mCurrentToken;
        return nullopt;
    }

    return foundType->second;
}

optional<vector<Statement>> Parser::parseFunctionBody()
{
    if (!expectOperator("{").has_value())
    {
        return nullopt;
    }

    vector<Statement> statements;

    while (!expectOperator("}").has_value())
    {
        optional<Statement> statement = expectStatement();
        if (statement.has_value())
        {
            statements.push_back(statement.value());
        }

        if (!expectOperator(";").has_value())
        {
            throw runtime_error("Expected ';' at end of statement.at line no " + to_string(mCurrentToken->mLineNumber));
        }
    }

    return statements;
}

void Parser::debugPrint() const
{
    for (auto funcPair : mFunctions)
    {
        funcPair.second.debugPrint();
    }
}

optional<Statement> Parser::expectOneValue()
{
    optional<Statement> result;
    if (mCurrentToken != mEndToken && mCurrentToken->mType == DOUBLE_LITERAL)
    {
        Statement doubleLiteralStatement;
        doubleLiteralStatement.mKind = StatementKind::DOUBLE_LITERAL;
        doubleLiteralStatement.mName = mCurrentToken->mText;
        doubleLiteralStatement.mType = Type("double", DOUBLE);
        result = doubleLiteralStatement;
        ++mCurrentToken;
    }
    else if (mCurrentToken != mEndToken && mCurrentToken->mType == INTEGER_LITERAL)
    {
        Statement integerLiteralStatement;
        integerLiteralStatement.mKind = StatementKind::INT_LITERAL;
        integerLiteralStatement.mName = mCurrentToken->mText;
        integerLiteralStatement.mType = Type("signed integer", INT32);
        result = integerLiteralStatement;
        ++mCurrentToken;
    }
    else if (mCurrentToken != mEndToken && mCurrentToken->mType == STRING_LITERAL)
    {
        Statement stringLiteralStatement;
        stringLiteralStatement.mKind = StatementKind::STRING_LITERAL;
        stringLiteralStatement.mName = mCurrentToken->mText;
        stringLiteralStatement.mType = Type("string", UINT8);
        result = stringLiteralStatement;
        ++mCurrentToken;
    }
    else if (mCurrentToken != mEndToken && mCurrentToken->mType == IDENTIFIER)
    {
        Statement stringLiteralStatement;
        stringLiteralStatement.mKind = StatementKind::VARIABLE;
        stringLiteralStatement.mName = mCurrentToken->mText;
        stringLiteralStatement.mType = Type();
        result = stringLiteralStatement;
        ++mCurrentToken;
    }
    else if (expectOperator("(").has_value())
    {
        result = expectExpression();
        if (!expectOperator(")").has_value())
        {
            throw runtime_error("Unbalanced '(' in parenthesized expression.at line no " + to_string(mCurrentToken->mLineNumber));
        }
    }
    if (!result.has_value())
    {
        result = expectFunctionCall();
    }
    return result;
}

optional<Statement> Parser::expectVariableAssignment()
{
    vector<Token>::iterator startToken = mCurrentToken;
    optional<Token> possibleVariableName = expectIdentifier();
    if (!possibleVariableName.has_value())
    {
        mCurrentToken = startToken;
        return nullopt;
    }

    Statement statement;

    statement.mKind = StatementKind::VARIABLE_ASSIGNMENT;
    statement.mName = possibleVariableName->mText;
    if (expectOperator("=").has_value())
    {
        optional<Statement> initialValue = expectExpression();
        if (!initialValue.has_value())
        {
            throw runtime_error("Expected initial value to right of '=' in variable declaration. at line no " + to_string(mCurrentToken->mLineNumber));
        }

        statement.mParameters.push_back(initialValue.value());
    }

    return statement;
}

optional<Statement> Parser::expectFunctionCall()
{
    vector<Token>::iterator startToken = mCurrentToken;

    optional<Token> possibleFunctionName = expectIdentifier();
    if (!possibleFunctionName.has_value())
    {
        mCurrentToken = startToken;
        return nullopt;
    }

    if (!expectOperator("(").has_value())
    {
        mCurrentToken = startToken;
        return nullopt;
    }

    Statement functionCall;
    functionCall.mKind = StatementKind::FUNCTION_CALL;
    functionCall.mName = possibleFunctionName->mText;

    while (!expectOperator(")").has_value())
    {
        optional<Statement> parameter = expectExpression();
        if (!parameter.has_value())
        {
            throw runtime_error("Expected expression as parameter. at line no " + to_string(mCurrentToken->mLineNumber));
        }
        functionCall.mParameters.push_back(parameter.value());

        if (expectOperator(")").has_value())
        {
            break;
        }
        if (!expectOperator(",").has_value())
        {
            // TODO: Check whether we still have a current token.
            throw runtime_error(string("Expected ',' to separate parameters, found '") + mCurrentToken->mText + "'." +"at line no " + to_string(mCurrentToken->mLineNumber));
        }
    }

    return functionCall;
}

optional<Statement> Parser::expectStatement()
{
    optional<Statement> result = expectExpression();
    if (!result.has_value())
    {
        result = expectVariableAssignment();
    }
    return result;
}

optional<Statement> Parser::expectExpression()
{ 
    vector<Token>::iterator startToken = mCurrentToken;
    optional<Statement> lhs = expectOneValue();
    //checking if the lhs is part of varible assignment or expression
    if(expectOperator("=").has_value()){
        mCurrentToken = startToken;
        return nullopt;
    }
    if(expectOperator("(").has_value()){
        mCurrentToken = startToken;
        return expectFunctionCall();
    }
    if (!lhs.has_value())
    {
        return nullopt;
    }

    while (true)
    {
        optional<Token> op = expectOperator();
        if (!op.has_value())
        {
            break;
        }
        int rhsPrecedence = operatorPrecedence(op->mText);
        if (rhsPrecedence == 0)
        {
            --mCurrentToken;
            return lhs;
        }
        optional<Statement> rhs = expectOneValue();
        if (!rhs.has_value())
        {
            --mCurrentToken;
            return lhs;
        }
        // get the righmost statement in lhs if rhspresedence is high to do modification according to precedence and  get the right structure
        Statement *rightmostStatementInLhs = findRightmostStatementInLhs(&lhs.value(), rhsPrecedence);
        if (rightmostStatementInLhs)
        {
            Statement operatorCall;
            operatorCall.mKind = StatementKind::OPERATOR_CALL;
            operatorCall.mName = op->mText;
            operatorCall.mParameters.push_back(rightmostStatementInLhs->mParameters.at(1));
            operatorCall.mParameters.push_back(rhs.value());
            rightmostStatementInLhs->mParameters[1] = operatorCall;
        }
        else
        {
            Statement operatorCall;
            operatorCall.mKind = StatementKind::OPERATOR_CALL;
            operatorCall.mName = op->mText;
            operatorCall.mParameters.push_back(lhs.value());
            operatorCall.mParameters.push_back(rhs.value());
            lhs = operatorCall;
        }
    }

    return lhs;
}

Statement *Parser::findRightmostStatementInLhs(Statement *lhs, size_t rhsPrecedence)
{
    if (lhs->mKind != StatementKind::OPERATOR_CALL)
    {
        return nullptr;
    }
    if (operatorPrecedence(lhs->mName) >= rhsPrecedence)
    {
        return nullptr;
    }

    Statement *rhs = &lhs->mParameters.at(1);
    rhs = findRightmostStatementInLhs(rhs, rhsPrecedence);
    if (rhs == nullptr)
    {
        return lhs;
    }
    return rhs;
}

size_t Parser::operatorPrecedence(const string &operatorName)
{
    map<string, OperatorEntry>::iterator foundOperator = sOperators.find(operatorName);
    if (foundOperator == sOperators.end())
    {
        return 0;
    }
    return foundOperator->second.mPrecedence;
}

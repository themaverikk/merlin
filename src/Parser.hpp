#pragma once

#include "Tokenizer.hpp"
#include "Type.hpp"
#include "FunctionDefinition.hpp"
#include "Statement.hpp"
#include "Interpreter.hpp"
#include <optional>
#include <string>
#include <map>
#include <vector>


    using namespace std;

    class Parser {
    public:
        Parser();
        void parse(vector<Token> &tokens);
        void debugPrint() const;
        map<string, FunctionDefinition> mFunctions;

    private:
        optional<Type> expectType();

        //! Empty string means match any identifier.
        optional<Token> expectIdentifier(const string& name = string());

        //! Empty string means match any operator.
        optional<Token> expectOperator(const string& name = string());

        bool expectFunctionDefinition();
        bool parseMainFunction();
        vector<Token>::iterator mCurrentToken;
        vector<Token>::iterator mEndToken;
        map<string, Type> mTypes;


        optional<vector<Statement>> parseFunctionBody();

        optional<Statement> expectOneValue();

        optional<Statement> expectStatement();

        optional<Statement> expectVariableAssignment();

        optional<Statement> expectFunctionCall();

        optional <Statement> expectExpression();

        size_t operatorPrecedence(const string &operatorName);

        Statement *findRightmostStatementInLhs(Statement *lhs, size_t rhsPrecedence);
    };


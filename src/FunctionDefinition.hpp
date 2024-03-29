#pragma once

#include "Type.hpp"
#include "Statement.hpp"
#include <string>
#include <vector>


    using namespace std;

    class ParameterDefinition {
    public:
        string mName; // Empty string means no name given.
        void debugPrint(size_t indent) const;
    };

    class FunctionDefinition {
    public:
        string mName;
        vector<ParameterDefinition> mParameters;
        vector<Statement> mStatements;

        void debugPrint() const;
    };

#ifndef PARSER
#define PARSER
#include <optional>
#include "lexer.hpp"
#include <vector>

class Parser
{
public:
    void parse(std::vector<Token> &tokens);

private:
    // empty string means match any possible indentifier
    std::optional<Token> expectIdentifier(const std::string &name = "");
    // empty string means match any possible operator
    std::optional<Token> expectOperator(const std::string &name = "");
    std::vector<Token>::iterator mCurrToken;
    std::vector<Token>::iterator mEndToken;
};

#endif 
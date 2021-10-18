#include "parser.hpp"
void Parser::parse(std::vector<Token> &tokens)
{
    mEndToken = tokens.end();
    mCurrToken = tokens.begin();
    //grammer
    while (mCurrToken != mEndToken)
    {
        std::optional<Token> possibleType = expectIdentifier();
        if (possibleType.has_value())
        { //we have a type
            std::optional<Token> possibleName = expectIdentifier();
            if (possibleName.has_value())
            {
                std::optional<Token> possibleOperator = expectOperator("(");
                if (possibleOperator.has_value())
                {
                    //we have a func
                    std::cout << "we have a fuc " << possibleName->lexeme() << std::endl;
                    exit(0);
                }
            }
        }
    }
}

std::optional<Token> Parser::expectIdentifier(const std::string &name)
{
    if (mCurrToken == mEndToken)
    {
        return std::nullopt;
    }

    if (mCurrToken->kind() != Token::Kind::Identifier)
    {
        return std::nullopt;
    }
    Token returnToken = *mCurrToken;
    ++mCurrToken;
    return returnToken;
}

std::optional<Token> Parser::expectOperator(const std::string &name)
{
    if (mCurrToken == mEndToken)
    {
        return std::nullopt;
    }
    if (mCurrToken->kind() != Token::Kind::LeftCurly)
    {
        return std::nullopt;
    }

    // if (std::find(Token::OPERATOR.begin(),Token::OPERATOR.end(),mCurrToken->kind()) == Token::OPERATOR.end())
    // {
    //     return std::nullopt;
    // }
    Token returnToken = *mCurrToken;
    ++mCurrToken;
    return returnToken;
}

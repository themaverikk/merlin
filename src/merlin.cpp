#include "parser.hpp"
#include "parser.cpp"
int main()
{
    while (true)
    {
        std::string input;
        int inputSize = input.size();
        while (inputSize == 0)
        {
            std::cout << "Merlin >>";
            getline(std::cin, input); // get input until enter key is pressed
            inputSize = input.size();
        }
        char inputInCharArray[inputSize]; // the lexer only accepts a char array
        for (int i = 0; i < inputSize; i++)
        {
            inputInCharArray[i] = input[i];
        }

        Lexer lex(inputInCharArray);
        std::vector<Token> tokens;
        for (Token token = lex.next();
             not token.is_one_of(Token::Kind::End, Token::Kind::Unexpected);
             token = lex.next())
        {
            std::cout << std::setw(12) << token.kind() << " |" << token.lexeme()
                      << "|\n";
            tokens.push_back(token);
        }
        Parser parser;
        parser.parse(tokens);
    }
}

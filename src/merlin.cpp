#include <stdio.h>
#include <iostream>
#include "lexer.hpp"
#include <string>
int main(){
    while(true){
        std::cout << "Merlin >>";

        std::string input;
        getline(std::cin, input); // get input until enter key is pressed
        int inputSize = input.size();
        if(inputSize>0){
            char inputInCharArray[inputSize]; // the lexer only accepts a char array
            for(int i = 0;i<inputSize;i++){
                inputInCharArray[i] = input[i];
            }
    
            Lexer lex(inputInCharArray);
    
            for (auto token = lex.next();
                not token.is_one_of(Token::Kind::End, Token::Kind::Unexpected);
                token = lex.next()) {
                    std::cout << std::setw(12) << token.kind() << " |" << token.lexeme()
                    << "|\n";
            }
        }
    }
}

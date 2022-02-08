#include "token.h"
#include <iostream>
#include <string>

Token::Token(int tokenType, std::string lexeme){
    m_type = tokenType;
    m_lexeme = lexeme;
}

void Token::print(void){
    std::cout << "TOKEN TYPE: " << m_type << " | " << "TOKEN LEXEME: " << m_lexeme << "\n";
};
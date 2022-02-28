#include "Token.h"
#include <iostream>
#include <string>

Token::Token(int tokenType, std::string lexeme, int line){
    m_type = tokenType;
    m_lexeme = lexeme;
    m_line = line;
}

void Token::print(void){
    std::cout << "TOKEN TYPE: " << tokenTypeString[m_type] << " | " << "TOKEN LEXEME: " << m_lexeme << " | " << "LINE: " << m_line << "\n";
};

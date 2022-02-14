#include "lexer.h"
#include <fstream>
#include <iostream>

//static variables need to be defined here
std::vector<Token> Lexer::m_tokens;


bool Lexer::tokenize(std::string file){

    //open source code file for reading
    std::fstream inputStream(file);
    //make sure it opened correctly
    if(!inputStream){
        std::cout << "ERROR READING SOURCE FILE" << "\n";
        return false;
    }

    char c{};
    char next{};
    std::string lexeme{};
    int currentLine = 0;
    //get the current char and peek the next char
    while(inputStream.get(c)){
        next = inputStream.peek();
        //ignore whitespace
        if(c == ' ' || c == '\t'){
            continue;
        }
        //increase line count
        else if(c == '\n'){
            currentLine++;
        }
        //see if the current character is a special character
        else if(findChar(c, specials)){
            m_tokens.emplace_back(TokenType::SPECIAL, std::string(1, c), currentLine);
        }
        //see if the current character is an operator
        else if(findChar(c, operators)){
            m_tokens.emplace_back(TokenType::OPERATOR, std::string(1, c), currentLine);
        }
        else{
            lexeme += c;
            if(next == ' '){
                determineLexeme(lexeme, currentLine);
            }
            else if(findChar(next, specials)){
                determineLexeme(lexeme, currentLine);
            }
        }
    }
    return true;

}

//determines if a lexeme is a keyword or identifier
void Lexer::determineLexeme(std::string& lexeme, int currentLine){
    if(findString(lexeme)){
        m_tokens.emplace_back(TokenType::KEYWORD, lexeme, currentLine);
    }
    else{
        m_tokens.emplace_back(TokenType::INDENTIFIER, lexeme, currentLine);
    }
    lexeme.clear();
}

//finds if given char is in the search vector
bool Lexer::findChar(char c, std::vector<std::string> searchVec){
    for(int i = 0; i < searchVec.size(); i++){
        if(c == *searchVec[i].c_str()){
            return true;
        }
    }
    return false;
}
//determines if a given lexeme is a keyword
bool Lexer::findString(std::string lexeme){
    for(int i = 0; i < keyWords.size(); i++){
        if(lexeme == keyWords[i]){
            return true;
        }
    }
    return false;
}

//prints current vector of tokens
void Lexer::printTokens(void){
    for(Token token : m_tokens){
        token.print();
    }
}
#include "lexer.h"
#include <fstream>
#include <iostream>

//static variables need to be defined here
std::vector<Token> Lexer::m_tokens;

//parses the characters from the source code file
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
    int currentLine = 1;
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
        //ignores comments
        else if(c == '#'){
            while(c != '\n'){
                inputStream.get(c);
            }
            currentLine++;
        }
        //start of a string
        else if(c == '"'){
            inputStream.get(c);
            while(c != '"'){
               lexeme += c;
               inputStream.get(c);
            }
            m_tokens.emplace_back(TokenType::LITERAL, lexeme, currentLine);
            lexeme.clear();
        }
        //start of a numerical constant
        else if(c >= '0' && c <= '9'){
            lexeme += c;
            while(next != ' ' && !findChar(next, specials)){
                inputStream.get(c);
                lexeme += c;
                next = inputStream.peek();
            }
            m_tokens.emplace_back(TokenType::NUMCONST, lexeme, currentLine);
            lexeme.clear();
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
            //while the next character isnt a space and its not a special character
            while(next != ' ' && !findChar(next, specials)){
                inputStream.get(c);
                lexeme += c;
                next = inputStream.peek();
            }
            determineLexeme(lexeme, currentLine);
        }
    }
    return true;
}

//determines if a lexeme is a keyword or identifier
void Lexer::determineLexeme(std::string& lexeme, int currentLine){
    for(int i = 0; i < keyWords.size(); i++){
        if(lexeme == keyWords[i]){
            m_tokens.emplace_back(TokenType::KEYWORD, lexeme, currentLine);
            lexeme.clear();
            return;
        }
    }
    m_tokens.emplace_back(TokenType::INDENTIFIER, lexeme, currentLine);
    lexeme.clear();
}

//finds if given char is in the search vector
bool Lexer::findChar(char c, std::vector<std::string> searchVec){
    for(int i = 0; i < searchVec.size(); i++){
        if(c == *searchVec[i].c_str()){ //c_str converts a string to a normal char array which needs to be de-referenced
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
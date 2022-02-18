#include "Lexer.h"
#include <fstream>
#include <iostream>

#define getChar(c) inputStream.get(c)
#define peekNext() inputStream.peek()

//static variables need to be defined here
std::vector<Token> Lexer::m_tokens;


//parses the characters from the source code file
void Lexer::tokenize(std::string file){
    //open source code file for reading
    std::fstream inputStream(file);
    //make sure it opened correctly
    if(!inputStream){
        std::cout << "ERROR READING SOURCE FILE" << "\n";
        exit(EXIT_FAILURE);
    }
    char c{};
    char next{};
    std::string lexeme{};
    int currentLine = 1;
    //get the current char and peek the next char
    while(getChar(c)){
        next = peekNext();
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
                getChar(c);
            }
            currentLine++;
        }
        //start of a string
        else if(c == '"'){
            getChar(c);
            //continually add chars until next quote is found
            while(c != '"'){
               lexeme += c;
               getChar(c);
            }
            addToken(TokenType::LITERAL, lexeme, currentLine);
        }
        //single character
        else if(std::string(1, c) == "'"){
            getChar(c);
            //continually add chars until ' is found
            //doing it this way will allowing for error checking later, if 
            //chars are longer than 1 character for instance
            while(std::string(1, c) != "'"){
                lexeme += c;
                getChar(c);
            }
            addToken(TokenType::CHARCONST, lexeme, currentLine);
        }
        //start of a numerical constant
        else if(c >= '0' && c <= '9'){
            lexeme += c;
            //continually add chars until a space or special char is found
            while(next != ' ' && !findChar(next, specials)){
                getChar(c);
                lexeme += c;
                next = peekNext();
            }
            addToken(TokenType::NUMCONST, lexeme, currentLine);
        }
        //see if the current character is a special character
        else if(findChar(c, specials)){
            m_tokens.emplace_back(TokenType::SPECIAL, std::string(1, c), currentLine);
        }
        //see if the current character is an operator
        //also determines if the operator is a dual operator(2 chars long)
        else if(findChar(c, operators)){
            switch(c){
                case '!':
                    determineNextChar(next, c, '=', currentLine);
                    break;
                case '>':
                    determineNextChar(next, c, '=', currentLine);
                    break;
                case '<':
                    determineNextChar(next, c, '=', currentLine);
                    break;
                case '|':
                    determineNextChar(next, c, '|', currentLine);
                    break;
                case '&':
                    determineNextChar(next, c, '&', currentLine);
                    break;
                case '/':
                    determineNextChar(next, c, '/', currentLine);
                    determineNextChar(next, c, '=', currentLine);
                    break;
                case '+':
                    determineNextChar(next, c, '=', currentLine);
                    determineNextChar(next, c, '+', currentLine);
                    break;
                case '-':
                    determineNextChar(next, c, '=', currentLine);
                    determineNextChar(next, c, '-', currentLine);
                    break;
                case '*':
                    determineNextChar(next, c, '=', currentLine);
                    determineNextChar(next, c, '*', currentLine);
                    break;
                default:
                    m_tokens.emplace_back(TokenType::OPERATOR, std::string(1, c), currentLine);
                    break;
            }
        }
        else{
            lexeme += c;
            //continually add chars while the next character isnt a space and its not a special character
            while(next != ' ' && !findChar(next, specials)){
                getChar(c);
                lexeme += c;
                next =  peekNext();
            }
            //is the lexeme a keyword or identifier?
            determineLexeme(lexeme, currentLine);
        }
    }
}

//adds a new token to token vector
void Lexer::addToken(int type, std::string& lexeme, int currentLine){
    m_tokens.emplace_back(type, lexeme, currentLine);
    lexeme.clear();
}

//determines if a lexeme is a keyword or identifier
void Lexer::determineLexeme(std::string& lexeme, int currentLine){
    for(int i = 0; i < keyWords.size(); i++){
        if(lexeme == keyWords[i]){
            addToken(TokenType::KEYWORD, lexeme, currentLine);
            return;
        }
    }
    addToken(TokenType::INDENTIFIER, lexeme, currentLine);
}

//determines if an operator is a double operator(two characters long)
void Lexer::determineNextChar(char next, char c, char op, int currentLine){
    if(next == op){
        m_tokens.emplace_back(TokenType::OPERATOR, std::string(2, c + next), currentLine);
    }
    else{
        m_tokens.emplace_back(TokenType::OPERATOR, std::string(1, c), currentLine);
    }
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

#ifndef LEXER_H
#define LEXER_H

#include "token.h"
#include <vector>
#include <string>

static std::vector<std::string> keyWords = {
    "func", "void", "in", "out", 
    "output", "int", "float", "char", 
    "array", "is", "or is", "finally is",
    "run", "if", "input", "main", "string"
};

static std::vector<std::string> operators = {
    "+", "-", "*", "/", "&", 
    "||", "=", "==", "!=", "?", ":"
};

static std::vector<std::string> specials = {
    "(", ")", "{", "}", 
    "[", "]", ";"
};

class Lexer{
    private:
        //in theory this vector will contain all tokens in an oak source 
        //code file
        static std::vector<Token> m_tokens;
    private:    
        Lexer(){};
        static bool findChar(char c, std::vector<std::string> searchVec);
        static bool findString(std::string lexeme);
        static void determineLexeme(std::string& lexeme, int currentLine);
    public:
        static bool tokenize(std::string file);
        static void printTokens(void);
};

#endif
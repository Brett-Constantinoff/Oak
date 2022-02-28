#ifndef LEXER_H
#define LEXER_H

#include "Token.h"
#include <vector>
#include <string>

static std::vector<std::string> keyWords = {
    "func", "void", "in", "out", 
    "output", "int", "float", "char", 
    "array", "is", "or", "finally",
    "run", "if", "input", "main", "string", 
    "construct"
};

static std::vector<std::string> operators = {
    "+", "-", "*", "/", "//", "&&", 
    "||", "=", "!=", "?", ":", "+=",
    "-=", "*=", "/=", "++", "--", "%", 
    "**", "<", ">", ">=", "<="
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
        static void addToken(int type, std::string& lexeme, int currentLine);
    public:
        static void tokenize(const char* file);
        static void printTokens(void);
};

#endif

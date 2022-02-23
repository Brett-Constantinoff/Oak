#include "Lexer.h"
#include <fstream>
#include <iostream>
#include <algorithm>

#define getChar(c) inputStream.get(c)
#define peekNext() inputStream.peek()

//static variables need to be defined here
std::vector<Token> Lexer::m_tokens;


//parses the characters from the source code file
void Lexer::tokenize(std::string file)
{
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
    while( getChar(c) )
    {
        next = peekNext();
        //ignore whitespace
        if( c == ' ' || c == '\t' )
        {
            continue;
        }
        //increase line count
        else if( c == '\n' )
        {
            currentLine++;
        }
        //ignores comments
        else if( c == '#' )
        {
            while( c != '\n' )
            {
                getChar(c);
            }
            currentLine++;
        }
        //start of a string
        else if( c == '"' )
        {
            getChar(c);
            //continually add chars until next quote is found
            while( c != '"' )
            {
               lexeme += c;
               getChar(c);
            }
            addToken(TokenType::LITERAL, lexeme, currentLine);
        }
        //single character
        else if( std::string(1, c) == "'" )
        {
            getChar(c);
            //continually add chars until ' is found
            //doing it this way will allowing for error checking later, if 
            //chars are longer than 1 character for instance
            while( std::string(1, c) != "'" )
            {
                lexeme += c;
                getChar(c);
            }
            addToken(TokenType::CHARCONST, lexeme, currentLine);
        }
        //start of a numerical constant
        else if( c >= '0' && c <= '9' )
        {
            lexeme += c;
            //continually add chars until a space or special char is found
            while( next != ' ' && !(std::find(specials.begin(), specials.end(), std::string(1, next)) != specials.end()) )
            {
                getChar(c);
                lexeme += c;
                next = peekNext();
            }
            addToken(TokenType::NUMCONST, lexeme, currentLine);
        }
        //see if the current character is a special character
        else if( std::find(specials.begin(), specials.end(), std::string(1, c)) != specials.end() )
        {
            m_tokens.emplace_back(TokenType::SPECIAL, std::string(1, c), currentLine);
        }
        //see if the current character is an operator
        //also determines if the operator is a dual operator(2 chars long)
        else if( std::find(operators.begin(), operators.end(), std::string(1, c)) != operators.end() )
        {
            if( std::find(operators.begin(), operators.end(), std::string(1, next)) != operators.end() )
            {
                m_tokens.emplace_back(TokenType::OPERATOR, std::string(1, c) + next, currentLine);
            }
            else
            {
                m_tokens.emplace_back(TokenType::OPERATOR, std::string(1, c) , currentLine);
            }
            getChar(c);
        }
        else
        {
            lexeme += c;
            //continually add chars while the next character isnt a space and its not a special character
            while(next != ' ' && !( std::find(specials.begin(), specials.end(), std::string(1, next)) != specials.end() ))
            {
                getChar(c);
                lexeme += c;
                next =  peekNext();
            }
            //is the lexeme a keyword or identifier?
            if( (std::find(keyWords.begin(), keyWords.end(), lexeme) != keyWords.end()) )
            {
                addToken(TokenType::KEYWORD, lexeme, currentLine);
            }
            else 
            {
                addToken(TokenType::INDENTIFIER, lexeme, currentLine);
            }
        }
    }
}

//adds a new token to token vector
void Lexer::addToken(int type, std::string& lexeme, int currentLine)
{
    m_tokens.emplace_back(type, lexeme, currentLine);
    lexeme.clear();
}

//prints current vector of tokens
void Lexer::printTokens(void)
{
    for(Token token : m_tokens)
    {
        token.print();
    }
}

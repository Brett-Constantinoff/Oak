#include "Lexer.h"
#include <fstream>
#include <iostream>
#include <algorithm>

#define getChar(c) inputStream.get(c)
#define peekNext() inputStream.peek()

//static variables need to be defined here
std::vector<Token> Lexer::m_tokens;


//parses the characters from the source code file
void Lexer::tokenize(const char* file)
{   
    FILE * fp;
    long size;
    char* buffer;
    char* current;
    char* next;
    size_t result;
    std::string lexeme;
    int currentLine = 1;

    //open file for reading
    fp = fopen(file, "rb");
    if( !fp ){
        std::cout << "ERROR OPENING SOURCE FILE" << "\n";
        exit(1);
    }
    
    //get size of file
    fseek(fp, 0, SEEK_END);
    size = ftell(fp);
    rewind(fp);

    //allocate memory
    buffer = new char[size];
    if( !buffer ){
        std::cout << "ERROR ALLOCATING MEMORY FOR SOURCE FILE" << "\n";
        exit(1);
    }

    //read file into memory
    result = fread(buffer, 1, size, fp);
    if( result != size ){
        std::cout << "ERROR READING FILE INTO ALLOCATED MEMORY" << "\n";
        exit(1);
    }

    current = buffer;
    next = current + 1;
    for(; current < buffer + size - 1; current++ )
    {   
        next = current + 1; 
        //ignore whitespace
        if( *current == ' ' || *current == '\t' )
        {   
            continue;
        }
        //increase line count
        else if( *current == '\n' )
        {
            currentLine++;
        }
        //ignores comments
        else if( *current == '#' )
        {
            while( *current != '\n' )
            {
                current++;
            }
            currentLine++;
        }
        //start of a string
        else if( *current == '"' )
        {
            current++;
            //continually add chars until next quote is found
            while( *current != '"' )
            {
               lexeme += *current;
               current++;
            }
            addToken(TokenType::LITERAL, lexeme, currentLine);
        }
        //single character
        else if( std::string(1, *current) == "'" )
        {
            current++;
            //continually add chars until ' is found
            //doing it this way will allowing for error checking later, if 
            //chars are longer than 1 character for instance
            while( std::string(1, *current) != "'" )
            {
                lexeme += *current;
                current++;
            }
            addToken(TokenType::CHARCONST, lexeme, currentLine);
        }
        //start of a numerical constant
        else if( *current >= '0' && *current <= '9' )
        {
            lexeme += *current;
            //continually add chars until a space or special char is found
            while( *next != ' ' && !(std::find(specials.begin(), specials.end(), std::string(1, *next)) != specials.end()) )
            {
                current++;
                lexeme += *current;
                next++;
            }
            addToken(TokenType::NUMCONST, lexeme, currentLine);
        }
        //see if the current character is a special character
        else if( std::find(specials.begin(), specials.end(), std::string(1, *current)) != specials.end() )
        {
            m_tokens.emplace_back(TokenType::SPECIAL, std::string(1, *current), currentLine);
        }
        //see if the current character is an operator
        //also determines if the operator is a dual operator(2 chars long)
        else if( std::find(operators.begin(), operators.end(), std::string(1, *current)) != operators.end() )
        {
            if( std::find(operators.begin(), operators.end(), std::string(1, *next)) != operators.end() )
            {
                m_tokens.emplace_back(TokenType::OPERATOR, std::string(1, *current) + *next, currentLine);
            }
            else
            {
                m_tokens.emplace_back(TokenType::OPERATOR, std::string(1, *current) , currentLine);
            }
            current++;
        }
        else
        {
            lexeme += *current;
            //continually add chars while the next character isnt a space and its not a special character
            while( *next != ' ' && !( std::find(specials.begin(), specials.end(), std::string(1, *next)) != specials.end() ))
            {
                current++;
                lexeme += *current;
                next++;
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


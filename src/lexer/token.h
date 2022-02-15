#ifndef TOKEN_H 
#define TOKEN_H
#include <string>

//these are all possible types for the token
//that i can think of right now, more might need to be added
enum TokenType{
    KEYWORD = 0, //type names, loops names, etc
    INDENTIFIER = 1, //variable & function names
    OPERATOR = 2, //+, -, /, =
    NUMCONST = 3, //50, 56.78
    CHARCONST = 4, // 'e', 't'
    LITERAL = 5, // "hello"
    SPECIAL = 6, // . , {}, (), []
};

class Token{
    private:
        int m_type{};
        std::string m_lexeme{};
    public:
        Token(int tokenType, std::string lexeme);
        void print(void);
};
#endif
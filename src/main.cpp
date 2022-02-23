#include "lexer/Lexer.h"
#include "lexer/Token.h"
#include "Timer.h"

int main(int args, char** argv)
{
   
   Timer::start();
   Lexer::tokenize("test/test1.oak");
   Timer::stop();
  
   Lexer::printTokens();

   return 0;
};  

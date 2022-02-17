#include "lexer/Lexer.h"
#include "lexer/Token.h"
#include "Timer.h"

#include <iostream>
#include <string>



int main(int args, char** argv){
   
   Timer::start();
   Lexer::tokenize("test/test1.oak");
   Timer::stop();
  
   
   //Lexer::printTokens();

   return 0;
};  
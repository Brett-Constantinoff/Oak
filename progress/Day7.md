# Date: 02/28/2022

## The Work

Its been a long and relaxing reading week and as such i didnt get much work done. Today i was just testing to see 
if i could make the code faster for the lexer and i succeeded. I got rid of my own searching functions and used C++'s 
built in searching methods as well as read the entire source file into memory and traversed the char array using pointers.
Along with this i removed some redundant checks for determining if a lexeme is an operator or not.
This drastically improved lexing speed by a factor of about 1.7 cutting the lexing speed from around 12 seconds / million lines of code to around 7 seconds / million lines. I also made it easier to see exactly what type of token is being saved.
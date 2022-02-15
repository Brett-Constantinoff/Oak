# Date: 02/14/2022

## The Work
Today I got my lexer to recognize whitespace (which it ingores), keywords, identifiers, special characters and operators.
All thats left is to recognize strings, comments, numerical constants. So far so good, I also added a 'current line' 
attribute to my token class which keeps track of which line the token occurs on. This will come in handy in the future
for error checking.

Identifiers will also need to be added to the symbol table (which is yet to be implemented) but one thing at a time

I came back and worked some more and got the lexer to identify all but char constants. Lots more testing and 
cleanup needs to be done but this is a win for today
# Date: 02/17/2022

## The Work

The lexer is pretty much completed i think, i need to do alot more testing just to make sure all cases work and 
nothing gets missed but so far so good. I also experimented with different methods of pushing elements to the 
vector of tokens and found out the using 'emplace_back' is much much faster than using 'push_back'. This is due
to the fact the emplace_back constructs the object in the vectors memory rather than in the main function memory and 
the vectors memory as is the case with push_back. Using a simple timer i found that emplace_back is close to 30x faster
than push_back.

Once testing is done and i have thought of all Oak's syntaxt ill begin work on constructing the symbol table which 
will hold all the identifers in the source code file.
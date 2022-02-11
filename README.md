# The Oak Programming Language
A WIP project to learn about compilers and programming languages

## The Plan for the Future
Over the next months, I will be attempting to create my own compiled programming language with the 
overall goal to learn about compilers, programming languages and to gain more experience in developing 
software using the C++ programming language.

This project is extremely ambitious and because of that progress will be slow, as I am a full time 
university student and I have other hobbies (Im not a complete nerd). But I thought it would be neat to 
document all my progress on the project, so I will create document for each day I work on Oak. This
doesnt mean I'll work on the project every day, but the days I do work on it will be documented.

## The End Goal
Obviously the end goal will be to create a working compiled programming language (duh). But I thought a 
good goal will be to write the 'fizz-buzz' function in Oak as it deals with control flow, functions, variables and most of what you need for a working programming language.

## What is Oak and Why Should You Care?
In the planning phase, Oak will be a statically typed, functional programming language with its own unique syntax but style similar to the C language. But should you care? Probably not

## Initial Syntax Design(tentative)

### Variables
Oak will suppport all the variables a typical language uses. This includes int, float, double, long, char, 
string, bool, as well as construct. A construct is Oak's version of struct.

Variables can be declared as follows: 
```
#this is a comment, and these are variabled declarations
int a;
string s;
bool b;
construct c;
```

Variables can be defined as follows: 
```
a{5};
s{"Hello"};
b{true};
c{
    float x{5.0};
    float y{10.0};
    float z{15.0};
};
```

Initializing a variable can be done in two ways, the first is by providing your own value and 
the second would be to provide the default value. The default values are:
* int: 0
* float: 0.0
* double: 0.0
* long: 0
* char: ''
* string: ""
* bool: true #notice the default value for bools is true

An example is as follows: 
```
int a{}; #a is initialized with 0
int b{5}; #b is initialized with 5
string s{} #s is initialized with an empty string
bool b{} #b is true
char c{'e'}; #c is intialized with 'e'
```

### Control Flow
The control flow will be handled a bit differently, Oak will use 'is, or is, finally' instead of 'if, else if, else' statments
```
int x{}; 
int y{};
input(x); //gets user input for x
input(y); //gets user input for y

is(x > y) ? {
    output(x);
}
or is(y > x) ? {
    output(y);
}
finally is(x == y) ? {
    output("x and y are equal");
}
```

### Loops
Oak will support two types of loop called a 'run' loop and an 'if' loop, which are essentially just a 'while' loop and 'for' loop
```
run(int x{5} > 1){
    output(x);
    x -= 1;
}

if(int y{5} : y -= 1){
    output(y);
}
```

### Functions
As with most asspects of this language, functions work very similarly to C languages. Functions are defined 
with the 'func' keyword followed by the return type and its name. Parameters to the function are passed into the
[] and start with the 'in' keyword. All functions require the 'out' key word even if the function returns void.
```
func int myFunction[in int x, in int y]{
    out x + y;
}
```

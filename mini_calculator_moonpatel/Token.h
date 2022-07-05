/*
==================GRAMMAR FOR EXPRESSION CALCULATOR===============
Expression:
    Term
    Term + Expression
    Term - Expression

Term:
    Primary
    Primary * Term
    Primary / Term

Primary:
    -Number
    Number
    constants like pi, e and so on
    '('Expression')'
    -'('Expression')'

Number:
    Floating point literal
    Integer
    results of functions like log(a,b), rt(a)

Input comes from cin through the Token_stream called ts
*/

#ifndef _TOKEN_H_
#define _TOKEN_H_

#include <string>
#include <queue>


// Token class has two members kind and value
// kind - represents the operator(+,- and so on) and represents a number if kind is '~'
// value - represents the value of the number if kind=='~' else it is zero
class Token {
public:
    char    kind;
    double  value;
    std::string name;
    Token();
    // Token(char,double,std::string); // constructer with args
    Token(char,double);
    Token(char,std::string);
};

// Token stream class which is used to read tokens from the user
// and also temporarily store users input in its buffer
class Token_stream {
private:
    std::queue<Token>   buffer;       // store the Token in buffer until it is received
    bool    isFull;        // tells whether the buffer is full or not
public:
    Token_stream();     // Default constructor
    Token get();        // to get a character from the input stream
    void  unget(Token token);       // to put back a character in the input stream
    void  flush();          // clears buffer
};

extern Token_stream ts; // used for input output of tokens in the program

// parser functions
double expression();    // read an expression
double term();          // read a term
double primary();       // read a primary
double declaration();   // read a declaration
double statement();     // read a statement

bool is_defined(std::string var);
double define_name(std::string var, double val);

bool ask();     // ask user whether to continue or exit program when an error occurs
void calculate();       // handles the expression calculation option

#endif
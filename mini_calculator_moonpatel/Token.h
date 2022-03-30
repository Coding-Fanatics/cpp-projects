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


// Token class has two members kind and value
// kind - represents the operator(+,- and so on) and represents a number if kind is '~'
// value - represents the value of the number if kind=='~' else it is zero
class Token {
public:
    char    kind;
    double  value;
    Token();
    Token(char,double); // constructer with args
};

// Token stream class which is used to read tokens from the user
// and also temporarily store users input in its buffer
class Token_stream {
private:
    Token   buffer;       // store the Token in buffer until it is received
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

bool ask();     // ask user whether to continue or exit program when an error occurs
bool calculate();       // handles the expression calculation option

#endif
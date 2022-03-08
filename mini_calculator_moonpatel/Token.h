#ifndef _TOKEN_H_
#define _TOKEN_H_

#include <string>

// some constants used in the program
const char NUM_KIND     = '~';      // Token with this kind represents a number
const char PROMPT       = '>';      // prompt the user to enter an expression
const char RESULT       = '=';      // followed by the result of the expression
const char QUIT         = 'q';      // Quit character for the program
const char TERMINATOR   = ';';      // represents the end of an expression
const char ADD          = '+';           
const char SUBTRACT     = '-';
const char MULTIPLY     = '*';
const char DIVIDE       = '/';
const char OPEN_PARA    = '(';
const char CLOASE_PARA  = ')';
const char PI_CHAR      = 'P';
const char EULER_CONSTANT_CHAR = 'E';
const std::string LINE  = "-------------------------------------------------------------------------------------------";

const int CALCULATE = 1;
const int NUMBER = 2;

// Scientific constants
const double PI = 3.14159265359;            // pi
const double EULER_CONSTANT  = 2.71828;     // e

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
void printline();       // print a line

bool calculate();       // handles the expression calculation option

#endif
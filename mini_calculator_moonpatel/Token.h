#ifndef _TOKEN_H_
#define _TOKEN_H_

// some constants used in the program
const char num_kind     = '~';      // Token with this kind represents a number
const char prompt       = '>';      // prompt the user to enter an expression
const char result       = '=';      // followed by the result of the expression
const char quit         = 'q';      // Quit character for the program
const char terminator   = ';';      // represents the end of an expression
const char add          = '+';           
const char subtract     = '-';
const char multiply     = '*';
const char divide       = '/';
const std::string line  = "-------------------------------------------------------------------------------------------";
const double pi           = 3.14;

// Token class has two members kind and value
// kind - represents the operator(+,- and so on) and represents a number if kind is '~'
// value - represents the value of the number if kind=='~' else it is zero
class Token {
public:
    char    kind;
    double  value;
    Token(char,double); // constructir with args
};

class Token_stream {
private:
    Token   buffer;       // store the Token in buffer until it is received
    bool    isFull;        // tells whether the buffer is full or not
public:
    Token_stream();     // Default constructor
    Token get();        // to get a character from the input stream
    void  unget(Token token);       // to put back a character in the input stream
    void  flush();          // clears buffer
    // Token_stream();
};

extern Token_stream ts; // used for input output of tokens in the program

// parser functions
double expression();    // read an expression
double term();          // read a term
double primary();       // read a primary

// ask user whether to continue or exit program when an error occurs
bool ask();

#endif
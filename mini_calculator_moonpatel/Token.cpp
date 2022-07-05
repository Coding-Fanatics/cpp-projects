#include <iostream>
#include <iomanip>
#include <cmath>
#include <map>

#include "Token.h"
#include "utils.h"

extern std::map<std::string, double> variables;

//=====================================================================================
// Token class member functions
//=====================================================================================

// Token::Token(char kind_val, double value_val, std::string name_val = std::string{})
//     : kind{kind_val}, value{value_val}, name{name_val} {}
Token::Token(char kind_val, double value_val)
    : kind{kind_val}, value{value_val}, name{} {}
Token::Token(char kind_val, std::string name_val = std::string{})
    : kind{kind_val}, value{0}, name{name_val} {}

Token::Token()
    : Token{0, 0} {}

// =====================================================================================
// Token_stream class member functions
// =====================================================================================

// Default constructor
Token_stream::Token_stream()
    : buffer{}, isFull{false} {}

// Get a token from the input stream
// Actually behind the scenes what happens is get()
// checks the buffer Token defined in Token_stream class and returns
// the buffer Token if it is not empty else it reads a Token from the standard input
Token Token_stream::get()
{
    if (isFull)
    {
        isFull = false; // set isFull to false indicating buffer queue is now empty
        Token temp = buffer.front();
        buffer.pop(); // clear the buffer queue
        return temp;  // return  a copy of element removec from queue
    }

    // if the buffer is empty
    char ch = 0;
    std::cin >> ch;

    switch (ch)
    {
    case '+':
    case '-':
    case '*':
    case '/':
    case ';':
    case 'q':
    case '(':
    case ')':
    case '=':
        return Token{ch, 0}; // return a Token

    // the token is a number
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
    {
        std::cin.unget(); // the character was not an operator
        double d;
        std::cin >> d; // read a double
        return Token{'~', d};
    }

    // pi
    case 'p':
    {
        std::cin >> ch;
        if (ch == 'i')
            return Token{PI_CHAR, 0};
        else
            throw std::runtime_error("bad format");
    }

    // eulers constant
    case 'e':
        return Token{EULER_CONSTANT_CHAR, 0};

    // a square root function
    case 'r':
        return Token{ch, 0};

    default:
        if(isalpha(ch)) {
            std::cin.putback(ch);
            std::string str;
            std::cin >> str;
            if(str==declaration_keyword) return Token{LET};
            return Token{NAME,str};
        }
        throw std::runtime_error("Bad token"); // some bad token obtained in input stream
        // return Token{};
    }
}

// putback a character in the input stream
// The character is stored in the buffer member of the Token_stream class
void Token_stream::unget(Token token)
{
    if (!isFull)
    {
        buffer.push(Token{token.kind, token.value}); // store the token in buffer queue
        isFull = true;
        return;
    }
    // else {
    //     throw std::runtime_error("Buffer is already full");     // the buffer is already full
    //     return;
    // }
}

// clear buffer
void Token_stream::flush()
{
    isFull = false;
    while (!buffer.empty())
        buffer.pop();
}

//=====================================================================================
// Parsing functions for our calculator
//=====================================================================================

// READ AN EXPRESSION
// Grammar for expression
// Expression:
//     Term
//     Term + Expression
//     Term - Expression
double expression()
{
    double d = term(); // get a term first

    Token token = ts.get(); // get a token
    switch (token.kind)
    {
    case '+':
        return (d + expression());

    case '-':
        ts.unget(token);
        return d + expression();

    // no expression after term
    default:
        ts.unget(token);
        return d;
    }
}

// READ A TERM
// Grammar for Term:
//     Primary
//     Primary * Term
//     Primary / Term
double term()
{
    double d = primary(); // read a primary first

    Token token = ts.get(); // read next token
    switch (token.kind)
    {
    case '*':
        return d * term();

    case '/':
    {
        double den = term();
        if (den == 0)
            throw std::runtime_error("cannot divide by zero");
        return d / den;
    }

    default: // if there is no term after current primary
        ts.unget(token);
        return d;
    }
}

// read a Primary
//
// Grammar for Primary:
//     -Number
//     Number
//     constants like pi, e and so on
//     '('Expression')'
//     -'('Expression')'
double primary()
{
    Token token = ts.get(); // receive a token from the input stream

    switch (token.kind)
    {
    // primary is '('Expression')'
    case '(':
    {
        double d = expression(); // read an expression
        Token t = ts.get();
        if (t.kind != ')')
            throw std::runtime_error("bad format");
        else
            return d;
    }

    // primary is -(some number)
    case SUBTRACT:
        return -primary();

    // primary is a number
    case NUM_KIND:
        return token.value;

    // primary is pi
    case PI_CHAR:
        return PI;

    // primary is euler's constant
    case EULER_CONSTANT_CHAR:
        return EULER_CONSTANT;

    // primary is a log function
    case 'l':
    {
        std::cin.unget();
        char *ch;
        std::cin.get(ch, INT32_MAX, '(');
        double d = expression();
        return std::log(d);
    }

    case 'r':
    {
        char c;
        std::cin >> c;
        if (c == 't')
        {
            double d = primary();
            if (d < 0)
                throw std::runtime_error("root function cannot have negative argument");
            else
                return std::sqrt(d);
        }
        else
            throw std::runtime_error("bad format");
    }

    // some error occured
    default:
        throw std::runtime_error("bad format");
    }
}


bool is_defined(std::string var) {
    auto itr = variables.find(var);
    if(itr!=variables.end())
        return true;
    else
        return false;
}
double define_name(std::string var, double val) {
    if(is_defined(var))
        throw var;
    else {
        variables[var] = val;
        return val;
    }
}

// ask whether to continue or exit when an error occurs
// bool ask() {
//     while(true) {

//     std::cout << "Do you want to continue(y/n)?" << std::endl;
//     printline();
//     char choice;
//     std::cout << PROMPT;
//     std::cin >> choice;

//     std::cin.ignore(10,'\n');   // ignore the remaining data

//     switch(choice) {
//         case 'y':
//         case 'Y':
//             return 0;

//         case 'n':
//         case 'N':
//             return 1;

//         default:
//             printline();
//             std::cout << "Incorrect choice" << std::endl;
//             break;
//         }
//     }
// }

// READ A DECLARATION
// Declaration:
//      "let" Name "=" Expression
double declaration()
{
    try
    {
        Token token = ts.get();
        if(token.kind!=NAME)
            throw std::runtime_error("Name expected in declaration");
        std::string var = token.name;
        if((token = ts.get()).kind!='=')
            throw std::runtime_error("= missing in the declaration of the variable" + token.name);

        double val=expression();

        return define_name(var,val);
    } catch(std::runtime_error &e) {
        std::cout << "Oops! Error occured in Token.cpp -> declaration()";
        std::cout << e.what() << "\n";
        return 0;
    }
    catch(std::string &str) {
        std::cout << "Variable " << str << " already declared.\n";
        return 0;
    }
}

// READ A STATEMENT
// Statement:
//      declaration
//      expression
double statement()
{
    Token token = ts.get();
    switch (token.kind)
    {
    case LET:
        return declaration();
    default:
        ts.unget(token);
        return expression();
    }
}

// handle the expression calculation part
void calculate()
{
    std::cout << "Expression calculator program" << std::endl;
    std::cout << "Please enter the expression you want to calculate below" << std::endl;
    std::cout << "(NOTE: Enter q to QUIT and ; after the end of an expression)" << std::endl;
    printline();

    while (true)
    {
        try
        {
            std::cout << PROMPT;
            Token token = ts.get();

            // check whether input is expression or QUIT command
            if (token.kind == QUIT)
                return; // exit
            else if (token.kind == TERMINATOR)
                continue; // read another expression
            else
                ts.unget(token); // input is expression, unget and read expression()

            // calculate the expression
            double ans = statement();
            ts.flush(); // flush out remaining TERMINATOR(';')

            std::cout << RESULT << std::fixed << std::setprecision(5) << ans << std::endl; // print the RESULT
        }
        catch (std::runtime_error &e)
        {
            printline();
            std::cout << "Error! ";
            std::cout << e.what() << std::endl;
            printline();

            std::cin.ignore(100, '\n'); // ignore until ; is reached
            ts.flush();                 // flush buffer

            // bool exit = ask();     // to continue or exit program?
            // if(exit)
            //     break;
            // }
        }
    }
}
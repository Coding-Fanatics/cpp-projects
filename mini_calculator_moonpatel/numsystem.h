#ifndef _NUMSYSTEM_H_
#define _NUMSYSTEM_H_

#include <string>

// codes for bases
const int BINARY_BASE = 2;
const int OCTAL_BASE = 8;
const int DECIMAL_BASE = 10;
const int HEXADECIMAL_BASE = 16;

// codes for choices
const char BINARY       = '1';
const char OCTAL        = '2';
const char DECIMAL      = '3';
const char HEXADECIMAL  = '4';

// number converter
void numberConverter();         // handles the number conversion option
std::string convertBinTo(std::string num, char type);    // to be implemented
std::string convertOctTo(std::string num, char type);
std::string convertDecTo(std::string num, char type);
std::string convertHexTo(std::string num, char type);
std::string decToBin(std::string num);        // convert decimal to a number of given base
std::string binToDec(std::string num);          // convert a number of given base to decimal

// validating functions
bool isBinary(std::string num);
bool isOctal(std::string num);
bool isDecimal(std::string num);
bool isHexadecimal(std::string num);

// formats binary numbers
std::string formatBinary(std::string num);

#endif
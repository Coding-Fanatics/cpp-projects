#ifndef _NUMSYSTEM_H_
#define _NUMSYSTEM_H_

#include <string>



// number converter
void printNumConverterMainMenu();
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

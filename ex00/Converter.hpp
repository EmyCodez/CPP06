#ifndef CONVERTER_HPP
#define CONVERTER_HPP

#include <string>
#include <iostream>
#include <iomanip>
#include <cmath>    // for std::isnan, std::isinf
#include <cctype>   // for std::isprint

enum LiteralType {
    CHAR,
    INT,
    FLOAT,
    DOUBLE,
    PSEUDO_LITERAL,
    INVALID
};

class Converter {
private:
    Converter();
    Converter(const Converter &other);
    Converter &operator=(const Converter &other);
    ~Converter();

    // Validation helpers
    static bool isSingleChar(const std::string &s);
    static bool isCharLiteral(const std::string &s);
    static bool isIntLiteral(const std::string &s);
    static bool isFloatLiteral(const std::string &s);
    static bool isDoubleLiteral(const std::string &s);
    static bool isPseudoLiteral(const std::string &s);
  
    public:
     // Helper to check if number is displayable
     static bool isDisplayable(char c);

    // Print helpers 
    static void printChar(double value);
    static void printInt(double value);
    static void printFloat(double value);
    static void printDouble(double value);

    // static method to detect type of literal
    static LiteralType detectType(const std::string &literal);

};

#endif // CONVERTER_HPP


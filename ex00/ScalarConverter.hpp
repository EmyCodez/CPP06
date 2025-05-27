#ifndef SCALARCONVERTER_HPP
#define SCALARCONVERTER_HPP

#include <iostream>
#include <string>
#include <climits>    // For INT_MIN, INT_MAX
#include <iomanip>    // For std::fixed, std::setprecision

class ScalarConverter
{
private:
    ScalarConverter();
    ScalarConverter(const ScalarConverter &other);
    ScalarConverter &operator=(const ScalarConverter &other);
    ~ScalarConverter();

    // Helper validation functions
    static bool isDisplayable(char c);
    static bool myIsNan(double x);
    static bool myIsInf(double x);

    // Helper print functions
    static void printChar(double value);
    static void printInt(double value);
    static void printFloat(double value);
    static void printDouble(double value);

public:
    static void convert(const std::string &literal);
};

#endif


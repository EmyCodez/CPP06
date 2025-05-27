# include "ScalarConverter.hpp"
# include <cmath>      // For isnan, isinf on some platforms (optional fallback)
# include <cerrno>
# include <cfloat>     // For DBL_MAX
# include <cstdlib>

// Constructors
ScalarConverter::ScalarConverter() {}

ScalarConverter::ScalarConverter(const ScalarConverter &other) { (void)other; }

ScalarConverter &ScalarConverter::operator=(const ScalarConverter &other) { 
    (void)other; return *this;
 }

ScalarConverter::~ScalarConverter() {}

// Checks if a char is printable displayable ASCII
bool ScalarConverter::isDisplayable(char c) {
    return c >= 32 && c <= 126;
}

// Check if double is NaN (since C++98 may lack std::isnan)
bool ScalarConverter::myIsNan(double x) {
    return x != x;
}

// Check if double is infinite (approximate check)
bool ScalarConverter::myIsInf(double x) {
    const double max = DBL_MAX; // from <cfloat>
    return (x > max || x < -max);
}

void ScalarConverter::printChar(double value) {
    if (myIsNan(value) || value < 0 || value > 127) {
        std::cout << "char: impossible\n";
        return;
    }
    char c = static_cast<char>(value);
    if (isDisplayable(c))
        std::cout << "char: '" << c << "'\n";
    else
        std::cout << "char: Non displayable\n";
}

void ScalarConverter::printInt(double value) {
    if (myIsNan(value) || value < static_cast<double>(INT_MIN) || value > static_cast<double>(INT_MAX)) {
        std::cout << "int: impossible\n";
        return;
    }
    int i = static_cast<int>(value);
    std::cout << "int: " << i << "\n";
}

void ScalarConverter::printFloat(double value) {
    float f = static_cast<float>(value);
    std::cout << std::fixed << std::setprecision(1);
    if (myIsNan(f))
        std::cout << "float: nanf\n";
    else if (myIsInf(f)) {
        if (f > 0)
            std::cout << "float: +inff\n";
        else
            std::cout << "float: -inff\n";
    } else {
        std::cout << "float: " << f << "f\n";
    }
}

void ScalarConverter::printDouble(double value) {
    std::cout << std::fixed << std::setprecision(1);
    if (myIsNan(value))
        std::cout << "double: nan\n";
    else if (myIsInf(value)) {
        if (value > 0)
            std::cout << "double: +inf\n";
        else
            std::cout << "double: -inf\n";
    } else {
        std::cout << "double: " << value << "\n";
    }
}

// The main conversion method, parses and prints all types
void ScalarConverter::convert(const std::string &literal) {
    double value = 0.0;

    // Use ternary for char literal detection
    value = (literal.size() == 3 && literal[0] == '\'' && literal[2] == '\'') ? static_cast<double>(literal[1]) :
            (literal.size() == 1 && isDisplayable(literal[0]) && !std::isdigit(static_cast<unsigned char>(literal[0]))) ? static_cast<double>(literal[0]) :
            0.0; // fallback 0, will parse below if literal not char

    if (value == 0.0 && !(literal.size() == 3 && literal[0] == '\'' && literal[2] == '\'') &&
        !(literal.size() == 1 && isDisplayable(literal[0]) && !std::isdigit(static_cast<unsigned char>(literal[0])))) {
        // parse double with possible 'f' stripped
        std::string tmp = literal;
        if (tmp[tmp.length() - 1] == 'f' && tmp != "inf" && tmp != "+inf" && tmp != "-inf") {
            tmp = tmp.substr(0, tmp.length() - 1);
        }

        char *endptr = NULL;
        errno = 0;
        value = std::strtod(tmp.c_str(), &endptr);

        if (errno != 0 || *endptr != '\0') {
            std::cout << "Error: invalid literal\n";
            return;
        }
    }

    printChar(value);
    printInt(value);
    printFloat(value);
    printDouble(value);
}


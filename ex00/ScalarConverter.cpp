# include "ScalarConverter.hpp"
# include "Converter.hpp"
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

// The main conversion method, parses and prints all types
void ScalarConverter::convert(const std::string &literal) {
    double value = 0.0;

    // Use ternary for char literal detection
    value = (literal.size() == 3 && literal[0] == '\'' && literal[2] == '\'') ? static_cast<double>(literal[1]) :
            (literal.size() == 1 && Converter::isDisplayable(literal[0]) && !std::isdigit(static_cast<unsigned char>(literal[0]))) ? static_cast<double>(literal[0]) :
            0.0; // fallback 0, will parse below if literal not char

    if (value == 0.0 && !(literal.size() == 3 && literal[0] == '\'' && literal[2] == '\'') &&
        !(literal.size() == 1 && Converter::isDisplayable(literal[0]) && !std::isdigit(static_cast<unsigned char>(literal[0])))) {
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

    Converter::printChar(value);
    Converter::printInt(value);
    Converter::printFloat(value);
    Converter::printDouble(value);
}


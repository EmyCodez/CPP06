# include "ScalarConverter.hpp"
# include "Converter.hpp"
# include <cerrno>
# include <cstdlib>
# include <climits>   

// Constructors
ScalarConverter::ScalarConverter() {}

ScalarConverter::ScalarConverter(const ScalarConverter &other) { (void)other; }

ScalarConverter &ScalarConverter::operator=(const ScalarConverter &other) { 
    (void)other; return *this;
 }

ScalarConverter::~ScalarConverter() {}

// Conversion method, parses and prints all types
void ScalarConverter::convert(const std::string &literal) {
    
    LiteralType type = Converter::detectType(literal);
    double value = 0.0;

    switch (type) {
        case CHAR:
            if (Converter::isCharLiteral(literal)) {
                    value = static_cast<double>(literal[1]);
            } else {
                    value = static_cast<double>(literal[0]);
            }
            break;

        case INT: {
            // Convert string to int, then to double
            errno = 0;
            char *endptr = NULL;
            long intVal = std::strtol(literal.c_str(), &endptr, 10);
            if (errno != 0 || *endptr != '\0' || intVal < INT_MIN || intVal > INT_MAX) {
                std::cout << "Error: invalid integer literal\n";
                return;
            }
            value = static_cast<double>(intVal);
            break;
        }

        case FLOAT: {
            // Convert string to float, strip trailing 'f'
            std::string tmp = literal.substr(0, literal.size() - 1); 
            errno = 0;
            char *endptr = NULL;
            float floatVal = std::strtof(tmp.c_str(), &endptr);
            if (errno != 0 || *endptr != '\0') {
                std::cout << "Error: invalid float literal\n";
                return;
            }
            value = static_cast<double>(floatVal);
            break;
        }

        case DOUBLE: {
            // Convert string to double
            errno = 0;
            char *endptr = NULL;
            value = std::strtod(literal.c_str(), &endptr);
            if (errno != 0 || *endptr != '\0') {
                std::cout << "Error: invalid double literal\n";
                return;
            }
            break;
        }

        case PSEUDO_LITERAL: {
            // Handle pseudo literals like nan, +inf, -inf etc.
            errno = 0;
            char *endptr = NULL;
            value = std::strtod(literal.c_str(), &endptr);
            break;
        }

        case INVALID:
        default:
            std::cout << "Error: invalid literal\n";
            return;
    }

    Converter::printChar(value);
    Converter::printInt(value);
    Converter::printFloat(value);
    Converter::printDouble(value);
}

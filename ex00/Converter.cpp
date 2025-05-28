# include "Converter.hpp"
# include <cstdlib>  
# include <cerrno>
# include <cctype>
# include <cstring>
# include <cmath>  
# include <climits> 
# include <iomanip> 

//constructors
Converter::Converter() {}

Converter::Converter(const Converter &other) {
      (void)other; 
}

Converter &Converter::operator=(const Converter &other) {
           (void)other;
   return *this;
}

Converter::~Converter() {}

// static helper functions
bool Converter::isSingleChar(const std::string &s) {
    return s.size() == 1 && std::isprint(static_cast<unsigned char>(s[0])) 
            && !std::isdigit(s[0]);
}

bool Converter::isCharLiteral(const std::string &s) {
    return s.size() == 3 && s[0] == '\'' && s[2] == '\'';
}

bool Converter::isIntLiteral(const std::string &s) {
    if (s.empty()) return false;
    size_t i = 0;
    if (s[0] == '+' || s[0] == '-')
        i++;
    if (i == s.size()) return false;
    for (; i < s.size(); i++) {
        if (!std::isdigit(static_cast<unsigned char>(s[i])))
            return false;
    }
    return true;
}

bool Converter::isFloatLiteral(const std::string &s) {
    if (s.empty() || s[s.size() - 1] != 'f') return false;
    std::string number = s.substr(0, s.size() - 1);
    const char *str = number.c_str();
    char *endptr;
    errno = 0;
    std::strtof(str, &endptr);
    return (*endptr == '\0' && errno == 0);
}

bool Converter::isDoubleLiteral(const std::string &s) {
    if (s.empty()) return false;
    const char *str = s.c_str();
    char *endptr;
    errno = 0;
    std::strtod(str, &endptr);
    return (*endptr == '\0' && errno == 0);
}

bool Converter::isPseudoLiteral(const std::string &s) {
    const char* pseudos[] = {
        "nan", "+nan", "-nan",
        "nanf", "+nanf", "-nanf",
        "inf", "+inf", "-inf",
        "inff", "+inff", "-inff"
    };
    for (int i = 0; i < 12; i++) {
        if (s == pseudos[i])
            return true;
    }
    return false;
}

// Checks if a char is printable displayable ASCII
bool Converter::isDisplayable(char c) {
    return c >= 32 && c <= 126;
}

void Converter::printChar(double value) {
    if (std::isnan(value) || value < 0 || value > 127) {
        std::cout << "char: impossible\n";
        return;
    }
    char c = static_cast<char>(value);
    if (isDisplayable(c))
        std::cout << "char: '" << c << "'\n";
    else
        std::cout << "char: Non displayable\n";
}

void Converter::printInt(double value) {
    if (std::isnan(value) || value < static_cast<double>(INT_MIN) || value > static_cast<double>(INT_MAX)) {
        std::cout << "int: impossible\n";
        return;
    }
    int i = static_cast<int>(value);
    std::cout << "int: " << i << "\n";
}

void Converter::printFloat(double value) {
    float f = static_cast<float>(value);
    std::cout << std::fixed << std::setprecision(1);

    if (std::isnan(f)) {
        std::cout << "float: nanf\n";
        return;
    }

    if (std::isinf(f)) {
        std::cout << "float: " << (f > 0 ? "+inff\n" : "-inff\n");
        return;
    }

    std::cout << "float: " << f << "f\n";
}

void Converter::printDouble(double value) {
    std::cout << std::fixed << std::setprecision(1);

    if (std::isnan(value)) {
        std::cout << "double: nan\n";
        return;
    }

    if (std::isinf(value)) {
        std::cout << "double: " << (value > 0 ? "+inf\n" : "-inf\n");
        return;
    }

    std::cout << "double: " << value << "\n";
}


// static method to detect type of literal
LiteralType Converter::detectType(const std::string &literal) {
    if (literal.empty()) return INVALID;

    if (isSingleChar(literal))
        return CHAR;

    if (isCharLiteral(literal)) return CHAR;
    if (isPseudoLiteral(literal)) return PSEUDO_LITERAL;
    if (isIntLiteral(literal)) return INT;
    if (isFloatLiteral(literal)) return FLOAT;
    if (isDoubleLiteral(literal)) return DOUBLE;
    return INVALID;
}


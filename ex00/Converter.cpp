#include "Converter.hpp"
#include <cstdlib>  // strtol, strtod, strtof not standard C++98 but available in C
#include <cerrno>
#include <cctype>
#include <cstring>

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


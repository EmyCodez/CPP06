#ifndef CONVERTER_HPP
#define CONVERTER_HPP

#include <string>

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

        // static helper functions
        static bool isSingleChar(const std::string &s);
        static bool isCharLiteral(const std::string &s);
        static bool isIntLiteral(const std::string &s);
        static bool isFloatLiteral(const std::string &s);
        static bool isDoubleLiteral(const std::string &s);
        static bool isPseudoLiteral(const std::string &s);

    public:
    // Static method 
    static LiteralType detectType(const std::string &literal);
};

#endif


#pragma once
#include <string>

namespace poker_hands {

    template<typename T>
    class Comparable
    {
    public:
        virtual bool operator>(const T& cp) = 0;
        virtual bool operator==(const T& cp) = 0;
        bool operator>=(const T& cp)
        {
            return (*this) > cp || (*this) == cp;
        }
        bool operator<(const T& cp)
        {
            return !(*this >= cp);
        }
        bool operator<=(const T& cp)
        {
            return !(*this > cp);
        }
        bool operator!=(const T& cp)
        {
            return !(*this == cp);
        }
    };

    class PokerException : public std::exception {
    public:
        std::string message;
        PokerException(std::string message) : message(message) {
        }
        virtual const char* what() const noexcept {
            return message.c_str();
        }
    };

    const std::string kVectorComparisonErrorMessage = "Incorrect vector sizes to compare. Should be the same length";

}

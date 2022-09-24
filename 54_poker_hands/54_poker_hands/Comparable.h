#pragma once
#include <string>

namespace poker_hands {

    template<typename T>
    class Comparable
    {
    public:
        virtual bool operator>(T& cp) = 0;
        virtual bool operator==(T& cp) = 0;
        bool operator>=(T& cp)
        {
            return (*this) > cp || (*this) == cp;
        }
        bool operator<(T& cp)
        {
            return !(*this >= cp);
        }
        bool operator<=(T& cp)
        {
            return !(*this > cp);
        }
        bool operator!=(T& cp)
        {
            return !(*this == cp);
        }
    };

    class PokerException : public std::exception {
    public:
        std::string msg;
        PokerException(std::string msg) : msg(msg) {
        }
        virtual const char* what() const noexcept {
            return msg.c_str();
        }
    };

    static const std::string entity_comparison_error_msg = "Invalid entity type for comparison";
    static const std::string vector_comparison_error_msg = "Incorrect vector sizes to compare. Should be the same length";

}

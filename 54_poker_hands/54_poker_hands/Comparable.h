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

}

#include <vector>

namespace poker_hands {

    /* Compares two vectors of the same size, of comparable type. Compares items
    subsequently from the first to the last.
    Used when two hands are of the same special type.*/
    template<typename T>
    bool operator>(std::vector<T>& vec1, std::vector<T>& vec2) {
        if (vec1.size() != vec2.size()) {
            throw PokerException(vector_comparison_error_msg);
        }
        int i = 0;
        while (i < vec1.size() && vec1[i] == vec2[i])
            i++;
        if (i == vec1.size())
            return false;
        else
            return vec1[i] > vec2[i];
    }

    template<typename T>
    bool operator==(std::vector<T>& vr1, std::vector<T>& vr2) {
        if (vr1.size() != vr2.size()) {
            throw PokerException(vector_comparison_error_msg);
        }
        for (int i = 0; i < vr1.size(); i++)
            if (vr1[i] != vr2[i])
                return false;
        return true;
    }

    template<typename T>
    bool operator>=(std::vector<T>& vec1, std::vector<T>& vec2) {
        return vec1 > vec2 || vec1 == vec2;
    }

    template<typename T>
    bool operator<(std::vector<T>& vec1, std::vector<T>& vec2) {
        return !(vec1 >= vec2);
    }

    template<typename T>
    bool operator<=(std::vector<T>& vec1, std::vector<T>& vec2) {
        return (vec1 > vec2);
    }

    template<typename T>
    bool operator!=(std::vector<T>& vec1, std::vector<T>& vec2) {
        return !(vec1 == vec2);
    }

}
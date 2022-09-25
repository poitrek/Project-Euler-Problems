//#include "tools.h"
//#include "Comparable.h"
//
//template<typename T>
//bool operator>(vector<T>& vec1, vector<T>& vec2) {
//    if (vec1.size() != vec2.size()) {
//        throw PokerException(kVectorComparisonErrorMessage);
//    }
//    int i = 0;
//    while (i < vec1.size() && vec1[i] == vec2[i])
//        i++;
//    if (i == vec1.size())
//        return false;
//    else
//        return vec1[i] > vec2[i];
//}
//
//template<typename T>
//bool operator==(vector<T>& vr1, vector<T>& vr2) {
//    if (vr1.size() != vr2.size()) {
//        throw PokerException(kVectorComparisonErrorMessage);
//    }
//    for (int i = 0; i < vr1.size(); i++)
//        if (vr1[i] != vr2[i])
//            return false;
//    return true;
//}
//
//template<typename T>
//bool operator>=(vector<T>& vec1, vector<T>& vec2) {
//    return vec1 > vec2 || vec1 == vec2;
//}
//
//template<typename T>
//bool operator<(vector<T>& vec1, vector<T>& vec2) {
//    return !(vec1 >= vec2);
//}
//
//template<typename T>
//bool operator<=(vector<T>& vec1, vector<T>& vec2) {
//    return (vec1 > vec2);
//}
//
//template<typename T>
//bool operator!=(vector<T>& vec1, vector<T>& vec2) {
//    return !(vec1 == vec2);
//}

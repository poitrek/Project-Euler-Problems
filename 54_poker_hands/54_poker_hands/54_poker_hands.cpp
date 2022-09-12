#include "54_poker_hands.hpp"

//bool compareHands(Hand &hand1, Hand &hand2) {
//    // prototype
//}
//const std::string Hand::card_code_pattern_string = "[23456789TJQKAtjqka][CDHScdhs]";


int main2()
{

    string word = "2C 3D 9H KC 4H";
    smatch hcp_match;
    if (regex_match(word, hcp_match, Hand::hand_code_pattern)) {
        cout << "yes" << endl;
        smatch ccp_match;
        auto match_begin = 
            sregex_iterator(word.begin(), word.end(), Hand::card_code_pattern);
        auto match_end = sregex_iterator();
        cout << "card codes:" << endl;
        for (sregex_iterator i = match_begin; i != match_end; ++i) {
            cout << "->" << (*i).str();
        }
        std::regex_search(word, ccp_match, Hand::card_code_pattern);
        cout << endl;
    }
    else {
        cout << "no" << endl;
    }

    //auto words_begin = sregex_iterator(word.begin(), word.end(),
    //    hand_code_pattern);
    //auto words_end = sregex_iterator();
    //cout << "Found " << distance(words_begin, words_end) << " 'words':" << endl;
    //for (sregex_iterator i = words_begin; i != words_end; ++i) {
    //    string match_str = (*i).str();
    //    cout << match_str << endl;
    //}
    return 0;
}
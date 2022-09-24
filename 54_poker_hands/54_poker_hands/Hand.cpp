#include "Hand.h"

#include "SpecialHandChecker.h"

namespace poker_hands {

    const std::string Hand::card_code_pattern_string = "[23456789TJQKAtjqka][CDHScdhs]";
    const std::regex Hand::card_code_pattern = std::regex(Hand::card_code_pattern_string);
    const std::regex Hand::hand_code_pattern = std::regex(
        "\\s*(?:(" + card_code_pattern_string + ")\\s+){4}(" +
        card_code_pattern_string + ")\\s*");

    Hand::Hand(Card c1, Card c2, Card c3, Card c4, Card c5) {
        cards = { c1, c2, c3, c4, c5 };
        sort(SortType::descending);
    }

    Hand::Hand(std::vector<Card>& cards) : cards(cards) {
        if (cards.size() != 5)
            throw PokerException("Incorrect number of cards in a hand");
        sort(SortType::descending);
    }

    Hand::Hand(std::string code) {
        std::smatch hcp_match;
        if (std::regex_match(code, hcp_match, Hand::hand_code_pattern)) {
            std::smatch ccp_match;
            auto match_begin =
                std::sregex_iterator(code.begin(), code.end(), Hand::card_code_pattern);
            auto match_end = std::sregex_iterator();
            for (std::sregex_iterator i = match_begin; i != match_end; ++i) {
                cards.push_back(Card((*i).str()));
            }
        }
        else {
            throw PokerException("Invalid hand code");
        }
        sort(SortType::descending);
    }

    void Hand::sort(SortType mode = descending) {
        if (mode == SortType::descending) {
            std::sort(cards.begin(), cards.end(), std::greater<>());
        }
        else {
            // ascending
            std::sort(cards.begin(), cards.end());
        }
    }

    std::pair<SpecialHand, std::vector<Rank>> Hand::highestSpecialHand() {
        SpecialHand highest_sh;
        std::vector<Rank> highest_check_result;
        // Iterate through all special hand checkers
        for (std::shared_ptr<SpecialHandChecker> handChecker : handCheckers) {
            std::vector<Rank> check_result = handChecker->check(*this);
            if (check_result != std::vector<Rank>()) {
                highest_check_result = check_result;
                highest_sh = handChecker->handType();
            }
        }
        return std::pair<SpecialHand, std::vector<Rank>>(highest_sh, highest_check_result);
    }

    bool Hand::operator>(Hand& hand) {
        auto p1 = this->highestSpecialHand();
        auto p2 = hand.highestSpecialHand();
        if (p1.first != p2.first)
            return p1.first > p2.first;
        else {
            return p1.second > p2.second;
        }
    }

    bool Hand::operator==(Hand& hand) {
        auto p1 = this->highestSpecialHand();
        auto p2 = hand.highestSpecialHand();
        return p1.first == p2.first && p1.second == p2.second;
    }

}

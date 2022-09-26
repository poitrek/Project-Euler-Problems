#include "Hand.h"

#include "SpecialHandChecker.h"

namespace poker_hands {

    const std::string Hand::kCardCodePatternString = "[23456789TJQKAtjqka][CDHScdhs]";
    const std::regex Hand::kCardCodePattern = std::regex(Hand::kCardCodePatternString);
    const std::regex Hand::kHandCodePattern = std::regex(
        "\\s*(?:(" + kCardCodePatternString + ")\\s+){4}(" +
        kCardCodePatternString + ")\\s*");
    const int Hand::kNumberOfCardsInHand = 5;

    const static std::vector<std::shared_ptr<SpecialHandChecker>> kHandCheckers = {
        std::shared_ptr<HighCardChecker>(new HighCardChecker),
        std::shared_ptr<PairChecker>(new PairChecker),
        std::shared_ptr<TwoPairChecker>(new TwoPairChecker),
        std::shared_ptr<ThreeOfKindChecker>(new ThreeOfKindChecker),
        std::shared_ptr<StraightChecker>(new StraightChecker),
        std::shared_ptr<FlushChecker>(new FlushChecker),
        std::shared_ptr<FullHouseChecker>(new FullHouseChecker),
        std::shared_ptr<FourOfKindChecker>(new FourOfKindChecker),
        std::shared_ptr<StraightFlushChecker>(new StraightFlushChecker),
        std::shared_ptr<RoyalFlushChecker>(new RoyalFlushChecker),
    };

    Hand::Hand(Card c1, Card c2, Card c3, Card c4, Card c5)
    : cards_({ c1, c2, c3, c4, c5 }) {
        Sort(SortType::kDescending);
    }

    Hand::Hand(std::vector<Card>& cards) : cards_(cards) {
        if (cards.size() != kNumberOfCardsInHand)
            throw HandInitializationException("Incorrect number of cards in a hand");
        Sort(SortType::kDescending);
    }

    Hand::Hand(std::string code) {
        std::smatch hcp_match;
        if (std::regex_match(code, hcp_match, Hand::kHandCodePattern)) {
            auto match_begin =
                std::sregex_iterator(code.begin(), code.end(), Hand::kCardCodePattern);
            auto match_end = std::sregex_iterator();
            for (std::sregex_iterator i = match_begin; i != match_end; ++i) {
                cards_.push_back(Card((*i).str()));
            }
        }
        else {
            throw HandInitializationException("Invalid hand code");
        }
        Sort(SortType::kDescending);
    }

    void Hand::Sort(SortType mode = kDescending) {
        if (mode == SortType::kDescending) {
            std::sort(cards_.begin(), cards_.end(), std::greater<>());
        }
        else {
            // ascending
            std::sort(cards_.begin(), cards_.end());
        }
    }

    std::pair<SpecialHand, std::vector<Rank>> Hand::HighestSpecialHand() const {
        SpecialHand highest_sh;
        std::vector<Rank> highest_check_result;
        // Iterate through all special hand checkers
        for (std::shared_ptr<SpecialHandChecker> handChecker : kHandCheckers) {
            std::vector<Rank> check_result = handChecker->Check(*this);
            if (check_result != std::vector<Rank>()) {
                highest_check_result = check_result;
                highest_sh = handChecker->HandType();
            }
        }
        return std::pair<SpecialHand, std::vector<Rank>>(highest_sh, highest_check_result);
    }

    bool Hand::operator>(const Hand& hand) {
        auto p1 = this->HighestSpecialHand();
        auto p2 = hand.HighestSpecialHand();
        if (p1.first != p2.first)
            return p1.first > p2.first;
        else {
            return p1.second > p2.second;
        }
    }

    bool Hand::operator==(const Hand& hand) {
        auto p1 = this->HighestSpecialHand();
        auto p2 = hand.HighestSpecialHand();
        return p1.first == p2.first && p1.second == p2.second;
    }

}

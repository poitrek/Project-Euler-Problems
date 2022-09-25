#include "Card.h"

namespace poker_hands {

    const std::unordered_map<char, Rank> Card::kRankCodes = {
        {'2', Rank::kTwo},
        {'3', Rank::kThree},
        {'4', Rank::kFour},
        {'5', Rank::kFive},
        {'6', Rank::kSix},
        {'7', Rank::kSeven},
        {'8', Rank::kEight},
        {'9', Rank::kNine},
        {'T', Rank::kTen},
        {'J', Rank::kJack},
        {'Q', Rank::kQueen},
        {'K', Rank::kKing},
        {'A', Rank::kAce}
    };

    const std::unordered_map<char, Suit> Card::kSuitCodes = {
        {'C', Suit::kClubs},
        {'D', Suit::kDiamonds},
        {'H', Suit::kHearts},
        {'S', Suit::kSpades}
    };

    bool Card::operator>(const Card& card) {
        return this->rank_ > card.rank_ || (this->rank_ == card.rank_ && this->suit_ > card.suit_);
    }

    bool Card::operator==(const Card& card) {
        return this->rank_ == card.rank_ && this->suit_ == card.suit_;
    }

}

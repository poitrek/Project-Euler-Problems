#include "Card.h"

namespace poker_hands {

    const std::unordered_map<char, Rank> Card::rank_codes = {
        {'2', Rank::two},
        {'3', Rank::three},
        {'4', Rank::four},
        {'5', Rank::five},
        {'6', Rank::six},
        {'7', Rank::seven},
        {'8', Rank::eight},
        {'9', Rank::nine},
        {'T', Rank::ten},
        {'J', Rank::jack},
        {'Q', Rank::queen},
        {'K', Rank::king},
        {'A', Rank::ace}
    };

    const std::unordered_map<char, Suit> Card::suit_codes = {
        {'C', Suit::clubs},
        {'D', Suit::diamonds},
        {'H', Suit::hearts},
        {'S', Suit::spades}
    };

    bool Card::operator>(Card& card) {
        return this->rank > card.rank || (this->rank == card.rank && this->suit > card.suit);
    }

    bool Card::operator==(Card& card) {
        return this->rank == card.rank && this->suit == card.suit;
    }

}

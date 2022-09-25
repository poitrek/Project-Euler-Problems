#pragma once
#include <unordered_map>

#include "Comparable.h"

namespace poker_hands {

    enum Suit
    {
        kSuitNone,
        kClubs,
        kDiamonds,
        kHearts,
        kSpades
    };

    enum Rank
    {
        kRankNone,
        kTwo,
        kThree,
        kFour,
        kFive,
        kSix,
        kSeven,
        kEight,
        kNine,
        kTen,
        kJack,
        kQueen,
        kKing,
        kAce
    };

    class Card : public Comparable<Card>
    {
    public:
        static const std::unordered_map<char, Rank> kRankCodes;
        static const std::unordered_map<char, Suit> kSuitCodes;
        Rank rank_;
        Suit suit_;
        Card() {
            rank_ = Rank::kRankNone;
            suit_ = Suit::kSuitNone;
        }
        Card(const std::string& card_code) {
            rank_ = Card::kRankCodes.at(card_code[0]);
            suit_ = Card::kSuitCodes.at(card_code[1]);
        }
        Card(Rank rank, Suit suit)
            : rank_(rank), suit_(suit) {}
        bool operator>(const Card& card) override;
        bool operator==(const Card& card) override;
    };

}
